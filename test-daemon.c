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
#include "debug-signal.h"
#include "string-extension.h"
#include "daemon.h"

static const char *sem_name = "/test-daemon";
static const char *harness_name = "./test-daemon-harness";
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
    debug_sigaction(sig, siginfo);
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
                return error("installing a handler for [%s] failed", strsignal(sig));

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
    debug_sigaction(sig, siginfo);
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
        return error("installing a handler for [%s] failed", strsignal(sig));

    return 0;
}

static int exec_harness() {
    char pid_str[16] = {0};
    string_from_int(pid_str, getppid());
    char *const argv[] = { (char *)harness_name, (char *)sem_name, pid_str };
    debug("execing [%s], sem name: [%s], test pid: [%s]",
        argv[0], argv[1], argv[2]);
    if (execve(harness_name, argv, NULL) == -1)
        return error("execing a harness failed");

    assert(0);
    return 0;
}

static int test_daemon_no_flags() {
    const char *mod_name = __func__;
    sigset_t sigset;
    mode_t sem_mode = S_IRUSR | S_IWUSR;
    unsigned sem_init_value = 0;
    unsigned sem_flag = O_CREAT | O_EXCL;
    sem_t *sem = NULL;
    pid_t harness_pid;

    log_init(mod_name);

    if (atexit(terminate))
        error("a termination handler could not be installed, [%s]", mod_name);

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

    switch ((harness_pid = fork())) {
    case -1: return error("forking a harness failed");
    case 0: return exec_harness();
    default: break;
    }

    sigemptyset(&sigset);
    for ( ; !process_started; ) {

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

    log_deinit(mod_name);

    return 0;
}

int main(void) {
    if (test_daemon_no_flags()) assert(0);

    exit(EXIT_SUCCESS);
}

