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

static void test_fetch_seq() {
    int e;
    const char *host = "127.0.0.1";
    unsigned short port = 8000;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    e = inet_pton(addr.sin_family, host, &addr.sin_addr);
    assert(e > 0);

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(fd != -1);
    e = connect(fd, (struct sockaddr *)(&addr), sizeof addr);
    assert(!e);

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

    e = close(fd);
}

int main(void) {
    test_fetch_seq();
    exit(EXIT_SUCCESS);
}

