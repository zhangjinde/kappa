/*
* tests for ingress routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include "kappa/error.h"
#include "kappa/ingress.h"

static void *start_ingress_thread(void *arg) {
    const char *host = "127.0.0.1";
    unsigned short port = 8008;
    unsigned short queue = 8;

    if (start_ingress(host, port, queue)) error(__func__);
}

static int test_accept_provider_input(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, fd;
    pthread_t ingress_thread;
    if ((e = pthread_create(
            &ingress_thread, NULL,
            start_ingress_thread, NULL
        )
    )) return 1;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if ((e = inet_pton(addr.sin_family, host, &addr.sin_addr)) != 1) return 1;

    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) return 1;
    if ((e = connect(fd, (struct sockaddr *)(&addr), sizeof addr))) return 1;

    int wbf[] = { 0, 0 };
    ssize_t nbw = 0;

    nbw = write(fd, wbf, sizeof wbf);
    assert(nbw == sizeof wbf);

    if ((e = close(fd))) return 1;

    return 0;
}

static int test_start_ingress(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    if (start_ingress(host, port, queue)) return 1;
    return 0;
}

int main(void) {
    const char *host = "127.0.0.1";
    unsigned short port = 8008;
    unsigned short queue = 8;

/*    if (test_start_ingress(host, port, queue)) exit(EXIT_FAILURE); */
    if (test_accept_provider_input(host, port, queue)) exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

