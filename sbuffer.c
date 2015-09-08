/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "sio_errors.h"
#include "sio_module.h"
#include "sio_buffer.h"

enum { nul = '\0' };

int string_set(char *buffer, size_t size, const char *format, ...) {
    va_list argv;
    va_start(argv, format);
    if((vsnprintf(buffer, size, format, argv)) >= size) {
        va_end(argv);
        return error(bytes_discarded);
    }
    va_end(argv);
    return 0;
}

int string_copy(char *buffer, size_t size, const char *source) {
    (void)memset(buffer, nul, size);
    strncpy(buffer, source, size - 1);
    return 0;
}

