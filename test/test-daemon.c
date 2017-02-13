/*
* tests for daemon routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "notused.h"
#include "log.h"
#include "error.h"
#include "trace.h"
#include "debug.h"
#include "stringlib.h"
#include "signallib.h"
#include "daemon.h"

static const char *mod_name;
static const char *const sem_name = "/test-daemon";
static const char *const harness_name = "./test-daemon-harness";
static const int sig_process_started = SIGUSR1;
static volatile sig_atomic_t process_started = 0;

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

static void process_started_handler(
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

    if (sig == sig_process_started)
        process_started = 1;

    errno = oerrno;
}

static int install_process_started_handler() {
    int sig = sig_process_started;
    struct sigaction sig_action;

    sig_action.sa_sigaction = process_started_handler;
    sig_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sig_action.sa_mask);

    if (sigaction(sig, &sig_action, NULL))
        return error(
            "installing a handler for [%s] failed",
            signal_signame(sig)
        );

    return 0;
}

static int spawn_harness() {
    pid_t test_pid, harness_pid;
    char test_pid_str[16] = {0};

    test_pid = getpid();

    switch ((harness_pid = fork())) {
    case -1: return error("forking a harness failed");
    case 0: break;
    default: return harness_pid;
    }

    assert(getppid() == test_pid);
    string_from_int(test_pid_str, test_pid);
    char *const argv[] = { (char *)harness_name, (char *)sem_name, test_pid_str };

    debug("execing [%s], sem name: [%s], test pid: [%s]", argv[0], argv[1], argv[2]);

    if (execve(harness_name, argv, NULL) == -1)
        return error("execing a harness failed");

    /* ought not to get to this point */
    assert(0);
    return 0;
}

static int test_daemon_no_flags() {
    sigset_t sigset;
    mode_t sem_mode = S_IRUSR | S_IWUSR;
    unsigned sem_init_value = 0;
    unsigned sem_flag = O_CREAT | O_EXCL;
    sem_t *sem = NULL;
    pid_t harness_pid;

    install_default_sigaction_handlers();

    if ((sem = sem_open(sem_name, sem_flag, sem_mode, sem_init_value)) == SEM_FAILED) {
        if (errno == EEXIST  && (sem_unlink(sem_name) == -1))
            return error("unlinking a semaphore [%s] failed, [%s]", sem_name, mod_name);
        return error("opening a semaphore [%s] failed, [%s]", sem_name, mod_name);
    }

    if (install_process_started_handler())
        return -1;

    sigfillset(&sigset);
    if ((sigprocmask(SIG_SETMASK, &sigset, NULL)))
        return error("setting a process signal mask failed");

    if ((harness_pid = spawn_harness()) == -1)
        return error("spawning a harness failed");

    sigemptyset(&sigset);
    for ( ; !process_started; ) {

        signal_trace_sigpending();

        if (sigsuspend(&sigset) == -1 && errno != EINTR)
            return error("suspending signals failed");

    }
    sigemptyset(&sigset);
    if ((sigprocmask(SIG_SETMASK, &sigset, NULL)))
        return error("setting a process signal mask failed");

    if (waitpid(harness_pid, NULL, WNOHANG) == -1)
        return error(
            "waiting for a harness process [%d] termination failed, [%s]",
            harness_pid, mod_name
        );

    if (sem_post(sem))
        return error("unlocking a semaphore [%s] failed, [%s]", sem_name, mod_name);

    if (sem_close(sem) == -1)
        return error("closing a semaphore [%s] failed, [%s]", sem_name, mod_name);

    if (sem_unlink(sem_name) == -1)
        return error("unlinking a semaphore [%s] failed, [%s]", sem_name, mod_name);

    return 0;
}

int main(int argc, const char **argv) {
    notused(argc);
    mod_name = argv[0];

    log_init(mod_name);

    if (atexit(terminate))
        error("a termination handler could not be installed, [%s]", mod_name);

    if (test_daemon_no_flags()) assert(0);

    log_deinit(mod_name);

    exit(EXIT_SUCCESS);
}

