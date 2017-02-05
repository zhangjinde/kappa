/*
* trace utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "log.h"
#include "trace.h"

enum { buffer_max_size = 0x0100 };

void trace(const char *fmt, ...) {
    char bf[buffer_max_size];
    va_list varg;
    const int error_num = errno;
    char *error_msg = NULL;

    if (error_num)
        error_msg = strerror(error_num);

    va_start(varg, fmt);

    memset(bf, 0, sizeof(bf));
    if (vsnprintf(bf, sizeof(bf), fmt, varg) >= sizeof(bf))
        log_warning("some of the characters were discarded from the message");

    va_end(varg);

    if (error_num) {
        if (snprintf(bf, sizeof(bf), "%s, %s: %d", bf, error_msg, error_num) >= sizeof(bf))
            log_warning("some of the characters were discarded from the message");
    }

    log_error(bf);
    errno = error_num;
}

