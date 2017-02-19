/*
* error utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <errno.h>
#include "kappa/log.h"
#include "kappa/error.h"

int error(const char *fmt, ...) {
    const int err_num = errno;
    va_list varg;

    va_start(varg, fmt);
    log_error(fmt, varg, err_num);
    va_end(varg);

    errno = err_num;
    return -1;
}

