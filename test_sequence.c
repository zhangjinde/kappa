/*
tests for sequence routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include "sequence.h"

static void test_sequence() {
    const char *host = "127.0.0.1";
    unsigned short port = 8000;
    unsigned short queue = 8;

    int e = start_sequence(host, port, queue); 
    assert(e==0);
}

int main(void) {
    test_sequence();
    exit(EXIT_SUCCESS);
}

