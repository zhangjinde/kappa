/*
* stream structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#define _POSIX_SOURCE

#include <errno.h>
#include <unistd.h>
#include "error.h"
#include "stream.h"

#define errors(err, nb) ((nb==-1) && (err!=0) && (err!=EINTR))
#define done(err, nb) !((err==EINTR) && (nb<0))

int stream_read(int fd, void *bf, size_t nb, ssize_t *nbr) {
    const void *bfh = bf;
    while ((*nbr = read(fd, bf, nb)) != 0) {
        if (errors(errno, *nbr)) return -1;
        bf += *nbr ? *nbr : 0;
        if (done(errno, *nbr)) break;
    }
    *nbr = (bf - bfh);
    return 0;
}

int stream_write(int fd, const void *bf, size_t nb, ssize_t *nbw) {
    const void *bfh = bf;
    while ((*nbw = write(fd, bf, (nb - (size_t)(bf - bfh)))) != 0) {
        if (errors(errno, *nbw)) return -1;
        bf += *nbw ? *nbw : 0;
        if (done(errno, *nbw)) break;
    }
    *nbw = (bf - bfh);
    return 0;
}

#undef done
#undef errors

