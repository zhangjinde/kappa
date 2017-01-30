/*
* tests for hash routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include "hash.h"

static int test_hash(int i, int n) {
    assert(hash(i, n) == hash(i, n));
    assert(hash(i, n) != hash(i, n*10));
    return 0;
}


int main(void) {
    if (test_hash(1, 100)) exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

