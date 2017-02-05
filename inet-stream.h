/*
* internet domain stream socket structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef INET_STREAM_H
#define INET_STREAM_H

int inet_stream_accept(int pfd, int *afd);

int inet_stream_make_address(
    struct sockaddr_in *addr,
    const char *host,
    unsigned short port
);

#endif

