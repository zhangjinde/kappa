/*
* tests for sequence routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include "stream.h"

static void test_stream_read() {
    int fd = open("/dev/null", O_RDONLY);
    char bf[1];
    size_t nb = sizeof bf;
    ssize_t nbr = 0;

    int e = stream_read(fd, bf, nb, &nbr);
    close(fd);
    assert(e == 0);
    assert(nbr == 0);
    assert(bf[0] == 0);
}

static void test_stream_write() {
    int fd = open("/dev/null", O_WRONLY);
    char bf[] = { 0 };
    size_t nb = sizeof bf;
    ssize_t nbw = 0;

    int e = stream_write(fd, bf, nb, &nbw);
    close(fd);
    assert(e == 0);
    assert(nbw == 1);
    assert(bf[0] == 0);
}

int main(void) {
    test_stream_read();
    test_stream_write();
    exit(EXIT_SUCCESS);
}

