/*
* sequence structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#define _POSIX_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "error.h"
#include "daemon.h"
#include "stream.h"
#include "sequence.h"

static int socket_close(int fd) {
    if (close(fd)) return -1;
    return 0;
}

static int socket_accept(int pfd, int *afd) {
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    *afd = accept(pfd, (struct sockaddr *)&addr, &addrlen);
    if (*afd < 0 && errno != EINTR) return -1;
    return *afd;
}

static int socket_listen(int fd, int queue) {
    if (listen(fd, queue)) return -1;
    return 0;
}

static int socket_bind(int fd, struct sockaddr_in *addr) {
    if (bind(fd, (struct sockaddr *)addr, sizeof(*addr))) return -1;
    return 0;
}

static int socket_make(int *fd) {
    if ((*fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
    return *fd;
}

static int address_make(struct sockaddr_in *addr, const char *host, unsigned short port) {
    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    switch (inet_pton(AF_INET, host, &addr->sin_addr)) {
    case 0: error("the address was not parseable"); return -1;
    case -1: error("an error occurred"); return -1;
    default: return 0;
    }
}

int start_sequence(const char *host, unsigned short port, unsigned short queue) {
    int e, fd, afd;
    struct sockaddr_in addr;
    char seq[] = { 0x30 };
    ssize_t nbw = 0;

    make_daemon(0, 0);
    if ((e = address_make(&addr, host, port)) == -1) return -1;
    if ((e = socket_make(&fd)) == -1) return -1;
    if ((e = socket_bind(fd, &addr)) == -1) return -1; 
    if ((e = socket_listen(fd, queue)) == -1) return -1;
    for ( ; (e = socket_accept(fd, &afd)); ) {
        if ((e = stream_write(afd, seq, sizeof seq, &nbw)) == -1) return -1;
        if ((e = socket_close(afd)) == -1) return -1;
    }
    if ((e = socket_close(fd)) == -1) return -1;

    return 0;
}

