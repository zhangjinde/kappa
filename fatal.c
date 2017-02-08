/*
* fatal utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <errno.h>
#include "log.h"
#include "fatal.h"

noreturn void fatal(const char *fmt, ...) {
    va_list varg;

    va_start(varg, fmt);
    log_fatal(fmt, varg, errno);
    va_end(varg);

    exit(EXIT_FAILURE);
}

