/*
* signal library of utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <string.h>
#include <errno.h>
#include <signal.h>
#include "error.h"
#include "trace.h"
#include "stringlib.h"
#include "signallib.h"

static const char *const signames[] = {
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

static void signal_trace(const sigset_t *sigset, const char *s) {
    int sig = 0;
    int sigc = 0;
    const char *signame = NULL;
    char b[0x0400] = {0};
    size_t bs = sizeof b;

    string_append(b, bs, "%s: [", s);
    for (sig = 1; sig < NSIG; sig++)
        if (sigismember(sigset, sig)) {
            if ((signame = signames[sig]))
                string_append(b, bs, sigc ? ", %s" : "%s", signame);
            sigc++;
        }
    string_append(b, bs, "]");

    trace(b);
}

const char *signal_signame(int sig) {
    return signames[sig];
}

void signal_trace_sigset(const sigset_t *sigset, const char *s) {
    const int oerrno = errno;

    signal_trace(sigset, s);
    errno = oerrno;
}

void signal_trace_sigaction(int sig, const siginfo_t *siginfo) {
    const int oerrno = errno;

    trace(
        "received a signal [%s], num: [%d], code: [%d], value: [%d], "
        "pid: [%d], uid: [%d]",
        signal_signame(sig), siginfo->si_signo, siginfo->si_code, siginfo->si_value,
        siginfo->si_pid, siginfo->si_uid
    );

    errno = oerrno;
}

void signal_trace_sigprocmask() {
    const int oerrno = errno;
    sigset_t sigset;
    const char *s = "blocked signals";

    if ((sigprocmask(SIG_BLOCK, NULL, &sigset))) {
        error("failed to obtain blocked signals");
        errno = oerrno;
        return;
    }

    signal_trace_sigset(&sigset, s);
    errno = oerrno;
}

void signal_trace_sigpending() {
    const int oerrno = errno;
    sigset_t sigset;
    const char *s = "pending signals";

    if ((sigpending(&sigset)) == -1) {
        error("failed to obtain pending signals");
        errno = oerrno;
        return;
    }

    signal_trace_sigset(&sigset, s);
    errno = oerrno;
}

