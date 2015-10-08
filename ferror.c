/*
* error utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "ferror.h"

enum { buffer_limit = 0x100 };

static void output(const char *format, va_list argv) {
    int sys_error = errno;
    char sb[buffer_limit];

    if((vsnprintf(sb, sizeof(sb), format, argv)) >= sizeof(sb))
        fprintf(stderr, "warning: characters discarded, [%d, %s]\n", errno, strerror(errno));

    fprintf(stderr, "error: %s, [%d, '%s']\n", sb, sys_error, strerror(sys_error));
    errno = 0;
}

int ferror_report(int value, ...) {
    const char *format = NULL;
    if(format) {
        va_list argv;
        va_start(argv, value);
        output(format, argv);
        va_end(argv);
    }
    return value;
}

int ferror_finally(struct closure *finally, int value, ...) {
    const char *format = NULL;
    if(format) {
        va_list argv;
        va_start(argv, value);
        output(format, argv);
        va_end(argv);
    }
    finally->func(finally);
    return value;
}

