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
#include "ingress.h"

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
    unsigned short port = 8010;
    unsigned short queue = 8;

    if (test_start_ingress(host, port, queue)) assert(0);
    exit(EXIT_SUCCESS);
}

