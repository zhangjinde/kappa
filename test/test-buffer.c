/*
* tests for buffer routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "kappa/buffer.h"

static int test_buffer_create() {
    int e;
    buffer_t *b = NULL;
    size_t bs = INT_MAX; 

    e = buffer_create(&b, bs);
    assert(!e);

    buffer_destroy(b);

    return 0;
}

int main(void) {
    if (test_buffer_create()) assert(0);

    exit(EXIT_SUCCESS);
}

