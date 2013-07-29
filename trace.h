/* trace utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef TRACE_H
#define TRACE_H

struct trace_attr {
    const char *program_name;
};

void trace(const char *format, ...);

#endif

