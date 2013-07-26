/* debug utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include "debug.h"

static const size_t MESSAGE_MAX_LENGTH = 256;

/* Writes a debug message to a system log. */
static void debug_write(const char *message, va_list varg) {
    char string[MESSAGE_MAX_LENGTH];
    vsnprintf(string, sizeof(string), message, varg);
    openlog("program name", LOG_CONS | LOG_PID, LOG_LOCAL0);
    syslog(LOG_DEBUG, "%s", string);
}

void debug(const char *message, ...) {
    va_list varg;
    va_start(varg, message);
    debug_write(message, varg);
    va_end(varg);
}

