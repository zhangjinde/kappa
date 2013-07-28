/* error utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "trace.h"
#include "error.h"

static const size_t MESSAGE_MAX_LENGTH = 256;

static void error_trace(const char *message, va_list varg) {
    char string[MESSAGE_MAX_LENGTH];
    vsnprintf(string, sizeof(string), message, varg);
    trace(string);
}

void error(int quit, const char *message, ...) {
    va_list vargs;
    va_start(vargs, format);
    error_trace(format, vargs);
    va_end(vargs);
    if(quit == 1) exit(EXIT_FAILURE);
}

