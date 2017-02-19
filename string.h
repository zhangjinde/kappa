/*
* string library of routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <stdarg.h>

void string_reverse(char *);
void string_from_int(char *, int);
int string_append(char *b, size_t bs, const char *s, ...);

#endif

