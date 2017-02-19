/*
* trace utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <errno.h>
#include "kappa/log.h"
#include "kappa/trace.h"

void trace(const char *fmt, ...) {
    const int err_num = errno;
    va_list varg;

    va_start(varg, fmt);
    log_trace(fmt, varg);
    va_end(varg);

    errno = err_num;
}

