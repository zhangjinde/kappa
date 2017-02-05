/*
* tests for error utility routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "log.h"
#include "error.h"

static int test_error() {
    int e;
    e = error("error: %d", 1);
    assert(e == -1);
    return 0;
}

static int test_error_no_varg() {
    int e;
    e = error("error");
    assert(e == -1);
    return 0;
}

static int test_error_errno() {
    int e;
    errno = 1;
    e = error("error: %s", __func__);
    assert(e == -1);
    return 0;
}

static int test_error_overflow() {
    int e;
    errno = 1;
    char bf[0x1000];
    memset(bf, '0', sizeof(bf));
    bf[sizeof(bf) - 1] = 0;
    e = error(bf);
    assert(e == -1);
    return 0;
}

int main(void) {
    log_init("test-error");
    if (test_error()) assert(0);
    if (test_error_no_varg()) assert(0);
    if (test_error_errno()) assert(0);
    if (test_error_overflow()) assert(0);
    exit(EXIT_SUCCESS);
}

