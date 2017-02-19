/*
* tests for error utility routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "kappa/log.h"
#include "kappa/error.h"

static int test_error_overflow() {
    int e;
    const char msg[] = "testing an error with overflow";
    char bf[0x1000];

    memcpy(bf, msg, sizeof(msg) - 1);
    memset(bf + sizeof(msg) - 1, '0', sizeof(bf) - sizeof(msg));
    bf[sizeof(bf) - 1] = 0;

    errno = 1;
    e = error(bf);

    assert(e == -1);
    assert(errno == 1);

    errno = 0;
    return 0;
}

static int test_error_noargs_noerrno() {
    int e;

    errno = 0;
    e = error("testing an error with no arguments and no errno");

    assert(e == -1);
    assert(errno == 0);

    errno = 0;
    return 0;
}

static int test_error_noargs_errno() {
    int e;

    errno = 1;
    e = error("testing an error with no arguments and with errno");

    assert(e == -1);
    assert(errno == 1);

    errno = 0;
    return 0;
}

static int test_error_args_noerrno() {
    int e;

    errno = 0;
    e = error(
        "testing an error with arguments [%s] and [%d] and with no errno",
        "string", 1
    );

    assert(e == -1);
    assert(errno == 0);

    errno = 0;
    return 0;
}

static int test_error_args_errno() {
    int e;

    errno = 1;
    e = error(
        "testing an error with arguments [%s] and [%d] and with errno [%d]",
        "string", 1, errno
    );

    assert(e == -1);
    assert(errno == 1);

    errno = 0;
    return 0;
}

int main(int argc, const char **argv) {
    assert(argc != 0);
    const char *module = argv[0];

    log_init(module);

    if (test_error_args_errno()) assert(0);
    if (test_error_args_noerrno()) assert(0);
    if (test_error_noargs_errno()) assert(0);
    if (test_error_noargs_noerrno()) assert(0);
    if (test_error_overflow()) assert(0);

    log_deinit(module);

    exit(EXIT_SUCCESS);
}

