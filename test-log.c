/*
* tests for log utility routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "log.h"

static int test_log_overflow() {
    va_list varg;
    const char msg[] = "testing logging a message with overflow";
    char bf[0x1000];

    memcpy(bf, msg, sizeof(msg) - 1);
    memset(bf + sizeof(msg) - 1, '0', sizeof(bf) - sizeof(msg));
    bf[sizeof(bf) - 1] = 0;

    log_debug(bf, varg);

    return 0;
}

static int test_log_varg_errno(int arg, ...) {
    va_list varg;

    errno = 1;
    va_start(varg, arg);
    log_error("testing logging a message with %s and errno", varg, errno);
    va_end(varg);

    assert(errno == 1);

    errno = 0;
    return 0;
}

static int test_log_no_varg() {
    va_list varg;

    log_debug("testing logging a message with no arguments", varg);

    return 0;
}

static int test_log_varg(int arg, ...) {
    va_list varg;

    va_start(varg, arg);
    log_debug("testing logging a debug message with %s", varg);
    va_end(varg);

    return 0;
}

int main(int argc, const char **argv) {
    assert(argc != 0);
    const char *module = argv[0];

    log_init(module);

    if (test_log_varg(0, "arguments")) assert(0);
    if (test_log_no_varg()) assert(0);
    if (test_log_varg_errno(0, "arguments")) assert(0);
    if (test_log_overflow()) assert(0);

    log_deinit(module);

    exit(EXIT_SUCCESS);
}

