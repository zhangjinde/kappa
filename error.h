/*
error utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa.
*/

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define error(s)\
fprintf(\
    stderr, "e: %s, n: %d, s: [%s], f: %s, l: %d\n", \
    s, errno, strerror(errno), __FILE__, __LINE__\
)

#endif

