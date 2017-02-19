/*
* tests for file routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "kappa/file.h"

static int test_file_remove() {
    int e;
    FILE *file;
    char filename[] = "/tmp/test-file-XXXXXXXX";

    e = mkstemp(filename); 
    e = file_create(filename, &file);
    assert(e == 0);
    assert(file);

    fclose(file);

    e = file_remove(filename);
    assert(e == 0);

    e = file_exists(filename);
    assert(e == 0);

    return 0;
}

static int test_file_create() {
    int e;
    FILE *file;
    char filename[] = "/tmp/test-file-XXXXXXXX";

    e = mkstemp(filename); 
    e = file_create(filename, &file);
    assert(e == 0);
    assert(file);

    fclose(file);
    remove(filename);

    return 0;
}

static int test_file_is_empty() {
    int e;

    e = file_is_empty("");
    assert(e == -1);

    e = file_is_empty("/dev/null");
    assert(e == 1);

    e = file_is_empty("/tmp");
    assert(e == 0);

    e = file_is_empty(NULL);
    assert(e == -1);

    return 0;
}


static int test_file_exists() {
    int e;

    e = file_exists("");
    assert(e == 0);

    e = file_exists("/dev/null");
    assert(e == 1);

    e = file_exists(NULL);
    assert(e == -1);

    return 0;
}

int main(void) {
    if (test_file_exists()) assert(0);
    if (test_file_is_empty()) assert(0);
    if (test_file_create()) assert(0);
    if (test_file_remove()) assert(0);

    exit(EXIT_SUCCESS);
}

