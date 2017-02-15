/*
* internet domain stream socket structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#define _BSD_SOURCE
#define _POSIX_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "error.h"
#include "inet-stream.h"

int inet_stream_accept(int pfd, int *afd) {
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    *afd = accept(pfd, (struct sockaddr *)(&addr), &addrlen);
    if (*afd < 0 && errno != EINTR)
        return error(
            "accepting a socket [%d] on the listening socket [%d] failed",
            *afd, pfd
        );

    return 0;
}

int inet_stream_make_address(
    struct sockaddr_in *addr,
    const char *host,
    unsigned short port
) {
    memset(addr, 0, sizeof *addr);
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    switch (inet_pton(AF_INET, host, &addr->sin_addr)) {
    case 0: return error("the address [%s] was not parseable", host);
    case -1: return error("parsing an inet address [%s] failed", host);
    default: return 0;
    }
}

