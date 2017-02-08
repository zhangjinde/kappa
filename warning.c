/*
* warning utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <errno.h>
#include "log.h"
#include "warning.h"

void warning(const char *fmt, ...) {
    const int err_num = errno;
    va_list varg;

    va_start(varg, fmt);
    log_warning(fmt, varg);
    va_end(varg);

    errno = err_num;
}

