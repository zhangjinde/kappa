/*
* stream structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef STREAM_H
#define STREAM_H

#include <sys/types.h>

/*
* reads from a file descriptor to a buffer
*/
int stream_read(int fd, void *bf, size_t nb, ssize_t *nbr);

/*
* writes to a file descriptor from a buffer
*/
int stream_write(int fd, const void *bf, size_t nb, ssize_t *nbw);

#endif

