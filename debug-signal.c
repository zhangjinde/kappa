/*
* debug signal utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <string.h>
#include <errno.h>
#include <signal.h>
#include "log.h"
#include "debug.h"
#include "debug-signal.h"

static const char *const sig_names[] = {
    [0] = NULL,
    [SIGHUP] = "HUP",
    [SIGINT] = "INT",
    [SIGQUIT] = "QUIT",
    [SIGILL] = "ILL",
    [SIGTRAP] = "TRAP",
    [SIGABRT] = "ABRT",
    [SIGEMT] = "EMT",
    [SIGFPE] = "FPE",
    [SIGKILL] = "KILL",
    [SIGBUS] = "BUS",
    [SIGSEGV] = "SEGV",
    [SIGSYS] = "SYS",
    [SIGPIPE] = "PIPE",
    [SIGALRM] = "ALRM",
    [SIGTERM] = "TERM",
    [SIGURG] = "URG",
    [SIGSTOP] = "STOP",
    [SIGTSTP] = "TSTP",
    [SIGCONT] = "CONT",
    [SIGCHLD] = "CHLD",
    [SIGTTIN] = "TTIN",
    [SIGTTOU] = "TTOU",
    [SIGIO] = "IO",
    [SIGXCPU] = "XCPU",
    [SIGXFSZ] = "XFSZ",
    [SIGVTALRM] = "VTALRM",
    [SIGPROF] = "PROF",
    [SIGWINCH] = "WINCH",
    [SIGINFO] = "INFO",
    [SIGUSR1] = "USR1",
    [SIGUSR2] = "USR2"
};

static void write_sigset(const sigset_t *sigset, const char *msg) {
    int sig = 0;
    int sigc = 0;
    const char *sig_name = NULL;
    char b[0x0400] = {0};
    char *bp = b;

    memmove(bp, msg, strlen(msg)), bp += strlen(bp);
    memmove(bp, ": [", 3), bp += strlen(bp);
    for (sig = 1; sig < NSIG; sig++)
        if (sigismember(sigset, sig)) {
            if ((sig_name = sig_names[sig])) {
                if (sigc) memmove(bp, ", ", 2), bp += strlen(bp);
                memmove(bp, sig_name, strlen(sig_name)), bp += strlen(bp);
            }
            sigc++;
        }

    if (!sigc) memmove(bp, "", 0), bp += strlen(bp);
    memmove(bp, "]", 1);

    bp = b;
    log_debug(bp, NULL);
}

const char *debug_signame(int sig) {
    return sig_names[sig];
}

void debug_sigaction(int sig, const siginfo_t *siginfo) {
    const int oerrno = errno;

    debug(
        "received a signal [%s], num: [%d], code: [%d], value: [%d], "
        "pid: [%d], uid: [%d]",
        debug_signame(sig), siginfo->si_signo, siginfo->si_code, siginfo->si_value,
        siginfo->si_pid, siginfo->si_uid
    );

    errno = oerrno;
}

void debug_sigset(const sigset_t *sigset, const char *msg) {
    const int oerrno = errno;

    write_sigset(sigset, msg);
    errno = oerrno;
}

void debug_sigprocmask() {
    const int oerrno = errno;
    sigset_t sigset;
    const char *msg = "blocked signals";

    if ((sigprocmask(SIG_BLOCK, NULL, &sigset))) {
        log_debug("failed to obtain blocked signals", NULL);
        errno = oerrno;
        return;
    }

    write_sigset(&sigset, msg);
    errno = oerrno;
}

void debug_sigpending() {
    const int oerrno = errno;
    sigset_t sigset;
    const char *msg = "pending signals";

    if ((sigpending(&sigset)) == -1) {
        log_debug("failed to obtain pending signals", NULL);
        errno = oerrno;
        return;
    }

    write_sigset(&sigset, msg);
    errno = oerrno;
}

