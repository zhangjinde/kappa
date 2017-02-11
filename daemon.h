/*
* daemon structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef DAEMON_H
#define DAEMON_H

typedef enum {
    daemon_flag_no_close_fds = 0x01,
    daemon_flag_no_reopen_stdfds = 0x02
} daemon_flag_t;

enum {
    daemon_default_maxfd = 0x1000
};

int make_daemon(daemon_flag_t flag, long maxfd);

#endif

