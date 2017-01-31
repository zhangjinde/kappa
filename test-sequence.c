/*
* tests for sequence routines
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
#include "sequence.h"
#include "sequence.h"

static int test_fetch_sequence(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, fd;

    if (start_sequence(host, port, queue)) return 1;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if ((e = inet_pton(addr.sin_family, host, &addr.sin_addr)) > 0) return 1;

    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) return 1;
    if ((e = connect(fd, (struct sockaddr *)(&addr), sizeof addr))) return 1;

    char wbf[] = { 0x01 };
    ssize_t nbw = 0;
    int rbf[2] = { 0 };
    ssize_t nbr = 0;

    nbw = write(fd, wbf, sizeof wbf);
    assert(nbw == 1);

    nbr = read(fd, rbf, sizeof(int));
    assert(nbr == sizeof(int));

    nbw = write(fd, wbf, sizeof wbf); 
    assert(nbw == 1);

    nbr = read(fd, rbf+1, sizeof(int));
    assert(nbr == sizeof(int));
    assert(rbf[0] == rbf[1]-1);

    if ((e = close(fd))) return 1;

    return 0;
}


static int test_start_sequence(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    if (start_sequence(host, port, queue)) return 1;
    return 0;
}

int main(void) {
    const char *host = "127.0.0.1";
    unsigned short port = 8000;
    unsigned short queue = 8;

    if (test_start_sequence(host, port, queue)) assert(0);
    if (test_fetch_sequence(host, port, queue)) assert(0);
    exit(EXIT_SUCCESS);
}

