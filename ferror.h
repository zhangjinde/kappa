/*
* error utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef FERROR_H
#define FERROR_H

#include "closure.h"

enum {
    unknown,
    stream_close_failed,
    stream_seek_failed,
    stream_tell_failed,
    file_open_failed,
    file_remove_failed,
    bytes_discarded
};

struct ferror_type {
    int value;
    const char *string;
};

const struct ferror_type const *(* get_ferror_type)(int error_id);
struct ferror_type { const int value; const char *format; };
int ferror_report(int value, ...);
int ferror_finally(struct closure *finally, int value, ...);

#endif

