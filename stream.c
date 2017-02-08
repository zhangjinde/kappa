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

#define errors(e, nb) ((nb == -1) && (e != 0) && (e != EINTR))
#define done(e, nb) !((e == EINTR) && (nb <0 ))

int stream_read(int fd, void *bf, size_t nb, ssize_t *nbr) {
    *nbr = 0;
    ssize_t cnbr;

    while ((cnbr = read(fd, bf, nb)) != 0) {
        if (errors(errno, cnbr))
            return error("reading from a file descriptor %d failed", fd);

        bf = (char *)bf + (cnbr ? cnbr : 0);
        *nbr += cnbr;

        if (done(errno, cnbr))
            break;
    }

    return 0;
}

int stream_write(int fd, const void *bf, size_t nb, ssize_t *nbw) {
    *nbw = 0;
    ssize_t cnbw;

    while ((cnbw = write(fd, bf, (nb - (size_t)*nbw))) != 0) {

        if (errors(errno, *nbw))
            return error("writing to a file descriptor %d failed", fd);

        bf = (const char *)bf + (*nbw ? *nbw : 0);
        *nbw += cnbw;

        if (done(errno, cnbw))
            break;
    }
    return 0;
}

#undef done
#undef errors

