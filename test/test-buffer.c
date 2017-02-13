/*
* tests for buffer routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

typedef enum {
    bar_f1 = 4
} bar_t;

struct foo {
    int foo_fn;
    char foo_fs[8];
    bar_t foo_fb;
};

static int test_buffer_create() {
    int e;
    FILE *f;

    struct foo xfoo = {
        .foo_fn = 8,
        .foo_fs = "foo",
        .foo_fb = bar_f1
    };

    f = fopen("./.foo", "w");
    fprintf(stderr, "f: [%px]\n", f);

    e = fwrite(&xfoo, sizeof xfoo, 1, f);
    fprintf(stderr, "fwrite e: [%d]\n", e);

    int is_eof = feof(f);
    fprintf(stderr, "is eof: [%d]\n", is_eof);

    int is_err = ferror(f);
    fprintf(stderr, "is err: [%d]\n", is_err);

    e = fclose(f);
    fprintf(stderr, "fclose e: [%d]\n", e);

    return 0;
}

int main(void) {
    if (test_buffer_create()) assert(0);

    exit(EXIT_SUCCESS);
}

