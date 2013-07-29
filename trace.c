/* trace utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include "trace.h"

static const size_t MESSAGE_MAX_LENGTH = 256;

static void trace_write(const char *message) {
    openlog("quux", LOG_CONS | LOG_PID, LOG_LOCAL0);
    syslog(LOG_NOTICE, "%s", message);
}

void trace(const char *format, ...) {
    va_list varg;
    va_start(varg, format);
    char message[MESSAGE_MAX_LENGTH];
    vsnprintf(message, sizeof(message), format, varg);
    trace_write(message);
    va_end(varg);
}

