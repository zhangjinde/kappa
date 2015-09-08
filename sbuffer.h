/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_BUFFER_H
#define SIO_BUFFER_H

int string_set(char *buffer, size_t size, const char *format, ...);
int string_copy(char *buffer, size_t size, const char *source);

#endif

