/*
* daemon structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "kappa/notused.h"
#include "kappa/error.h"
#include "kappa/trace.h"
#include "kappa/debug.h"
#include "kappa/signal.h"
#include "kappa/daemon.h"

static void terminate(void) {
    trace("terminated a process");
}

static void default_sigaction_handler(
    int sig,
    siginfo_t *siginfo,
    void *context
) {
    const int oerrno = errno;
    notused(context);

#ifndef NDEBUG
/* not async-signal-safe */
    signal_trace_sigaction(sig, siginfo);
#endif

    errno = oerrno; 
}

static int install_default_sigaction_handlers() {
    int sig;
    struct sigaction sig_action;

    sig_action.sa_sigaction = default_sigaction_handler;
    sig_action.sa_flags = SA_SIGINFO;
    sigfillset(&sig_action.sa_mask);

    for (sig = 1; sig < NSIG; sig++)
        if (sig != SIGSTOP && sig != SIGKILL)
            if (sigaction(sig, &sig_action, NULL))
                return error(
                    "installing a handler for [%s] failed",
                    signal_signame(sig)
                );

    return 0;
}

static int exec_fork() {
    switch (fork()) {
    case -1: return error("executing a fork failed");
    case 0: return 0;
    default: _exit(EXIT_SUCCESS);
    }
}

static int close_fds(long maxfd) {
    const int oerrno = errno;
    int fd;

    maxfd = ((maxfd = sysconf(_SC_OPEN_MAX)) == -1) ?
        daemon_default_maxfd : maxfd;

    for (fd = 0; fd < maxfd; fd++)
        (void)close(fd);

    errno = oerrno;
    return 0;
}

static int reopen_stdfds() {
    const int oerrno = errno;
    int fd;

    (void)close(STDIN_FILENO);

    if ((fd = open("/dev/null", O_RDWR)) != STDIN_FILENO)
        return error("reopening a file descriptor %d failed", STDIN_FILENO);

    if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
        return error(
            "duplicating a file descriptor %d onto %d failed",
            STDIN_FILENO, STDOUT_FILENO
        );

    if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
        return error(
            "duplicating a file descriptor %d onto %d failed",
            STDIN_FILENO, STDERR_FILENO
        );

    errno = oerrno;
    return 0;
}

int make_daemon(daemon_flag_t flag, long maxfd) {
    int e;

    if ((e = exec_fork()))
        return e;

    if (setsid() == -1)
        return error("creating a new session failed");

    if ((e = exec_fork()))
        return e;

    if (!(flag & daemon_flag_no_close_fds))
        if ((e = close_fds(maxfd)))
            return e;

    if (!(flag & daemon_flag_no_reopen_stdfds))
        if ((e = reopen_stdfds()))
            return e;

    if (atexit(terminate))
        return error("a termination handler could not be installed");

    if (install_default_sigaction_handlers())
        return error("default signal handlers could not be installed");

    return 0;
}

