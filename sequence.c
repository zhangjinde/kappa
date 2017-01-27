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
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "error.h"
#include "daemon.h"
#include "stream.h"
#include "sequence.h"

static int seqnum = 0x30;
static int consumerfds[8] = { 0 };
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int accept_socket(int pfd, int *afd);

static int get_nfds() {
    int *fd;
    for (fd = consumerfds; *fd; fd++);
    return (fd - consumerfds) ? (*--fd + 1) : 0;
}

static int provide_sequence() {
    int e, fd, *cfd, nfds = 0;
    fd_set readfds;
    ssize_t nbr, nbw;
    int wbf[] = { 0 };
    char rbf[] = { 0 };

    for (;;) {
        if ((e = pthread_mutex_lock(&mutex))) return -1;

        while (!(nfds = get_nfds())) pthread_cond_wait(&cond, &mutex);

        FD_ZERO(&readfds);
        for (cfd = consumerfds; *cfd; cfd++) FD_SET(*cfd, &readfds);

        if ((e = pthread_mutex_unlock(&mutex))) return -1;
        if ((e = select(nfds, &readfds, NULL, NULL, NULL)) == -1) return -1;

        for (fd = 0; fd < nfds; fd++) {
            if (FD_ISSET(fd, &readfds)) {
                wbf[0] = seqnum;
                if ((e = stream_read(fd, rbf, sizeof rbf, &nbr))) return -1;
                if ((e = stream_write(fd, wbf, sizeof wbf, &nbw))) return -1;
                ++seqnum;
            }
        }
    }
}

static int accept_consumer(int pfd) {
    for (int afd, e; ; afd = e = 0) {
        e = accept_socket(pfd, &afd);
        if ((e = pthread_mutex_lock(&mutex))) return -1;
        for (int *cfd = consumerfds; *cfd; cfd++);
        *cfd = afd;
        if ((e = pthread_mutex_unlock(&mutex))) return -1;
        if ((e = pthread_cond_signal(&cond))) return -1;
    }
}

static int accept_socket(int pfd, int *afd) {
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    *afd = accept(pfd, (struct sockaddr *)(&addr), &addrlen);
    if (*afd < 0 && errno != EINTR) return -1;
    return 0;
}

static int make_address(
    struct sockaddr_in *addr,
    const char *host,
    unsigned short port
) {
    memset(addr, 0, sizeof *addr);
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    switch (inet_pton(AF_INET, host, &addr->sin_addr)) {
    case 0: error("the address was not parseable"); return -1;
    case -1: error("undefined error"); return -1;
    default: return 0;
    }
}

int start_sequence(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, pfd;
    struct sockaddr_in addr;
    pthread_t accept_consumers, provide_sequences;

    if ((e = make_daemon(0, 0))) return -1;
    if ((e = make_address(&addr, host, port))) return -1;

    if ((pfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
    if ((e = bind(pfd, (struct sockaddr *)(&addr), sizeof addr))) return -1;
    if ((e = listen(pfd, queue))) return -1;

    if ((e = pthread_create(&accept_consumers, NULL, accept_consumer, pfd)))
        return -1;

    if ((e = pthread_create(&provide_sequences, NULL, provide_sequence, NULL)))
        return -1;

    if ((e = pthread_join(accept_consumers, NULL))) return -1;
    if ((e = pthread_join(provide_sequences, NULL))) return -1;

    if ((e = close(pfd))) return -1;

    return 0;
}

