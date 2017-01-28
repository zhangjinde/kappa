/*
tests for daemon routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "daemon.h"

static void test_daemon() {
    int e, pid;

    pid = getpid();
    e = make_daemon(0x03, 0);

    assert(e == 0);
    assert(pid != getpid());
    assert(getppid() == 1);
    assert(getpid() != getpgid(0));
    assert(getsid(0) == getpgid(0));
}

int main(void) {
    test_daemon();
    exit(EXIT_SUCCESS);
}

