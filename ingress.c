/*
* ingress structures and routines
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
#include "kappa/error.h"
#include "kappa/daemon.h"
#include "kappa/stream.h"
#include "kappa/ingress.h"

static int providerfds[0x10000] = { 0 };
static int providerbf[0x1000000000] = { 0 };
enum { provider_msg_nb = sizeof(int) * 2 };
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int accept_socket(int pfd, int *afd);

static int get_nfds() {
    int *fd;
    for (fd = providerfds; *fd; fd++);
    return (fd - providerfds) ? (*--fd + 1) : 0;
}

static int accept_provider_input(void) {
    int e, *fd, *afd, nfds = 0;
    fd_set readfds;
    ssize_t nbr;
    int rbf[0x10000] = { 0 };

    for (;;) {
        if ((e = pthread_mutex_lock(&mutex))) return -1;
        while (!(nfds = get_nfds())) pthread_cond_wait(&cond, &mutex);

        FD_ZERO(&readfds);
        for (afd = providerfds; *afd; afd++) FD_SET(*afd, &readfds);

        if ((e = select(nfds, &readfds, NULL, NULL, NULL)) == -1) return -1;

        for (fd = providerfds; *fd; fd++) {
            if (FD_ISSET(*fd, &readfds)) {
                if ((e = stream_read(*fd, rbf, sizeof rbf, &nbr))) return -1;
                long nmsg = nbr / provider_msg_nb;
                for (int i = 0; i != nmsg; i++) {
                    providerbf[i] = rbf[i];
                }
            }
        }

        if ((e = pthread_mutex_unlock(&mutex))) return -1;
    }
}

static int accept_provider(int pfd) {
    for (int afd, e; ; afd = e = 0) {
        e = accept_socket(pfd, &afd);
        if ((e = pthread_mutex_lock(&mutex))) return -1;
        for (int *fd = providerfds; *fd; fd++);
        *fd = afd;
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

int start_ingress(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, pfd;
    struct sockaddr_in addr;
    pthread_t accept_provider_thread, accept_provider_input_thread;

/*    if ((e = make_daemon(3, 0))) return -1; */
    if ((e = make_address(&addr, host, port))) return -1;

    if ((pfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
    if ((e = bind(pfd, (struct sockaddr *)(&addr), sizeof addr))) return -1;
    if ((e = listen(pfd, queue))) return -1;

    if ((e = pthread_create(
            &accept_provider_thread,
            NULL,
            (void *(*)(void *))accept_provider,
            (void *)(intptr_t)pfd
        )
    ))
        return -1;

    if ((e = pthread_create(
            &accept_provider_input_thread,
            NULL,
            (void *(*)(void *))accept_provider_input,
            NULL
        )
    ))
        return -1;

    if ((e = pthread_join(accept_provider_input_thread, NULL))) return -1;
    if ((e = pthread_join(accept_provider_thread, NULL))) return -1;

    if ((e = close(pfd))) return -1;

    return 0;
}

