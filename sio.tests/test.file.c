/* simple io tests
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "../sio_file.h"

static void test_file_created() {
    const char *url = ".output/file";
    int rv;
    rv = file_create(url);
    assert(!rv);
}

static void test_file_exists() {
    const char *url = ".output/file";
    int rv;
    rv = file_create(url);
    rv = file_exists(url);
    assert(rv == 1);
}

static void test_file_does_not_exist() {
    const char *url = ".output/not";
    int rv;
    rv = file_exists(url);
    assert(rv == 0);
}


int main(int argc, char **argv) {
    test_file_created();
    test_file_exists();
    test_file_does_not_exist();
}

