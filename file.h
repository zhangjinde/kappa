/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_FILE_H
#define SIO_FILE_H

int file_exists(const char *url);
int file_is_empty(const char *url);
int file_create(const char *url);
int file_remove(const char *url);

#endif

