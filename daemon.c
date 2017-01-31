/*
* daemon structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "daemon.h"

static int fork_s() {
    switch (fork()) {
    case -1: return -1;
    case 0: return 0;
    default: _exit(EXIT_SUCCESS);
    }
}

static void close_fds(long maxfd) {
    int fd;

    maxfd = ((maxfd = sysconf(_SC_OPEN_MAX)) == -1) ?
        daemon_default_maxfd : maxfd;

    for (fd=0; fd<maxfd; fd++)
        close(fd);
}

static int reopen_stdfds() {
    int fd;
    close(STDIN_FILENO);
    fd = open("/dev/null", O_RDWR);
    if (fd != STDIN_FILENO) return -1;
    if ((dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)) return -1;
    if ((dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)) return -1;
    return 0;
}

int make_daemon(int flag, long maxfd) {
    if (fork_s() == -1) return -1;
    if (setsid() == -1) return -1;
    if (fork_s() == -1) return -1;
    if (!(flag & flag_no_close_fds)) close_fds(maxfd);
    if (!(flag & flag_no_reopen_stdfds)) reopen_stdfds();

    return 0;
}

