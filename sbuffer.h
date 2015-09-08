/*
* string buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef SBUFFER_H
#define SBUFFER_H

int sbuffer_set(char *bf, size_t nb, const char *fmt, ...);
int sbuffer_copy(char *bf, size_t nb, const char *src);

#endif

