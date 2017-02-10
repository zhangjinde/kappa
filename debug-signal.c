/*
* debug signal utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <string.h>
#include <errno.h>
#include "log.h"
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

const char *debug_signame(int sig) {
    return sig_names[sig];
}

void debug_sigset(const sigset_t *sigset) {
    const int err_num = errno;
    int sig = 0;
    const char *sig_name = NULL;
    const char *fmt = "signal set: ";
    char buf[0x0400] = {0};
    char *bufp = buf;

    memmove(bufp, fmt, strlen(fmt));
    bufp += strlen(bufp);
    for (sig = 1; sig < NSIG; sig++)
        if (sigismember(sigset, sig))
            if ((sig_name = sig_names[sig])) {
                memmove(bufp, "[", 1);
                bufp += strlen(bufp);
                memmove(bufp, sig_name, strlen(sig_name));
                bufp += strlen(bufp);
                memmove(bufp, "]", 1);
            }

    bufp = buf;
    va_list varg;
    log_debug(bufp, varg);

    errno = err_num;
}

