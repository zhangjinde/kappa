/*
* string buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "error.h"
#include "module.h"
#include "sbuffer.h"

int sbuffer_set(char *bf, size_t nb, const char *fmt, ...) {
    va_list argv;
    va_start(argv, format);
    if ((vsnprintf(bf, nb, fmt, argv)) >= nb) {
        va_end(argv);
        return error(bytes_discarded);
    }
    va_end(argv);
    return 0;
}

int sbuffer_copy(char *bf, size_t nb, const char *src) {
    (void)memset(bf, '\0', nb);
    strncpy(bf, src, nb - 1);
    return 0;
}

