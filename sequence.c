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
#include "debug.h"
#include "stream.h"
#include "daemon.h"
#include "sequence.h"

struct sequence {
    int pfd;
    int nafds;
    int hafds;
    pthread_t threads[0x01];
    int afds[0x0100];
};

static void sigaction_handler(
    int sig,
    siginfo_t *siginfo,
    void *context
) {
    debug("sig %d %s\n", sig, __func__); 
    if (sig == SIGINT || sig == SIGTERM) return;
    if (sig == SIGSEGV) exit(EXIT_FAILURE);
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

static int service(struct sequence *sequence) {
    int e, sig, fd, afd, nsfds;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    fd_set readfds, sreadfds;
    ssize_t nbr, nbw;
    char wbf[0x02] = { 0 };
    char rbf[0x10] = { 0 };

    struct sigaction sig_action;
    sig_action.sa_sigaction = sigaction_handler;
    sig_action.sa_flags = SA_SIGINFO;
    sigfillset(&sig_action.sa_mask);
    for (sig = 1; sig < 32; sig++)
        if (
            sig != SIGTSTP && sig != SIGSTOP &&
            sig != SIGQUIT && sig != SIGKILL
        )
            if ((e = sigaction(sig, &sig_action, NULL)))
                error("sigaction failed");

    FD_ZERO(&readfds);
    for (fd = 0; fd <= sequence->hafds; fd++)
        if (sequence->afds[fd]) FD_SET(fd, &readfds);

    for (;;) {

        sreadfds = readfds;
        if ((nsfds = select(sequence->hafds + 1, &sreadfds, NULL, NULL, NULL)) == -1)
            error("selecting on readfds failed");

        for (fd = 0; fd <= sequence->hafds && nsfds; fd++) {

            if (FD_ISSET(fd, &sreadfds)) {

                --nsfds;

                if (fd == sequence->pfd) {

                    afd = accept(fd, (struct sockaddr *)(&addr), &addrlen);
                    if (afd < 0 && errno != EINTR)
                        error("accepting a socket failed");

                    sequence->afds[afd] = 1;
                    ++sequence->nafds;
                    if (sequence->hafds < afd) sequence->hafds = afd;
                    FD_SET(afd, &readfds);
                    continue;
                }

                if ((e = stream_read(fd, rbf, sizeof rbf, &nbr)))
                    error("reading from a socket failed");

                if (!nbr) {

                    FD_CLR(fd, &readfds);

                    if ((e = close(fd)))
                        error("closing a socket failed");

                    sequence->afds[fd] = 0;
                    --sequence->nafds;
                    continue;
                }

                wbf[0] = 0x30;
                if ((e = stream_write(fd, wbf, sizeof wbf, &nbw)))
                    error("writing to a socket failed");
            }
        }
    }
}

int sequence_create(
    sequence_t **sequence,
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, pfd;
    struct sockaddr_in addr;

    if (!(*sequence = (struct sequence*)malloc(sizeof(struct sequence))))
        return error("a sequence could not be allocated%s", __func__);
    
    if ((e = make_address(&addr, host, port)))
        return error("a socket address could not be created %s", __func__);

    if ((pfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return error("a socket could not be created %s", __func__);

    if ((e = bind(pfd, (struct sockaddr *)(&addr), sizeof addr)))
        return error("a socket could not be bound %s", __func__);

    if ((e = listen(pfd, queue))) {
        return error("a socket could not listen %s", __func__);
    }

    (*sequence)->pfd = pfd;
    memset((*sequence)->afds, 0, sizeof (*sequence)->afds);
    (*sequence)->afds[pfd] = 1;
    (*sequence)->nafds = 1;
    (*sequence)->hafds = pfd;

    if ((e = pthread_create(
            &(*sequence)->threads[0],
            NULL,
            (void *(*)(void *))service,
            (void *)*sequence
        )
    )) return error("sequence service thread could not be created %s", __func__);

    if ((e = pthread_join((*sequence)->threads[0], NULL))) return 1;
    if ((e = close(pfd))) return 1;

    return 0;
}

