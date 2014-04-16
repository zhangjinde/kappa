/* simple io tests
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "../sio_buffer.h"

static void test_set_s_buffer_zero_source_null() {
    char sb[] = { '\0' };
    char source[] = {};
    string_copy(sb, sizeof sb, source);

    assert((sizeof sb) == 1);
    assert(strlen(sb) == 0);
    assert(*(sb) == '\0');
}

static void test_set_s_buffer_one_source_one() {
    char sb[] = { '0', '\0' };
    char source[] = { '0', '\0' };
    string_copy(sb, sizeof sb, source);

    assert((sizeof sb) == 2);
    assert(strlen(sb) == 1);
    assert(*(sb) == *(source));
    assert(*(sb + 1) == '\0');
}

static void test_set_s_buffer_zero_source_one() {
    char sb[] = { '\0' };
    char source[] = { '0', '\0' };
    string_copy(sb, sizeof sb, source);

    assert((sizeof sb) == 1);
    assert(strlen(sb) == 0);
    assert(*(sb) == '\0');
}

static void test_set_s_buffer_some_source_one() {
    size_t sbs = sizeof(char) * 8;
    char *sb = malloc(sbs);
    char source[] = { '0', '\0' };
    string_copy(sb, sbs, source);

    assert(strlen(sb) == 1);
    assert(*(sb) == '0');
    assert(*(sb + 1) == '\0');

    free(sb);
}

static void test_set_s_buffer_one_source_some() {
    size_t sbs = sizeof(char) * 2;
    char *sb = malloc(sbs);
    *(sb + sbs - 1) = '\0';
    size_t source_size = sizeof(char) * 8;
    char *source = malloc(source_size);
    memset(source, '0', source_size - 1);
    *(source + source_size - 1) = '\0';
    string_copy(sb, sbs, source);

    assert(strlen(sb) == 1);
    assert(*(sb) == '0');
    assert(*(sb + 1) == '\0');

    free(sb);
    free(source);
}

static void test_set_fv_buffer_zero_format_null_argv_none() {
    char sb[] = { '\0' };
    char format[] = {};
    string_set(sb, sizeof sb, format);

    assert((sizeof sb) == 1);
    assert(strlen(sb) == 0);
    assert(*(sb) == '\0');
}

static void test_set_fv_buffer_one_format_null_argv_none() {
    char sb[] = { '0', '\0' };
    char format[] = { '\0' };
    string_set(sb, sizeof sb, format);

    assert((sizeof sb) == 2);
    assert(strlen(sb) == 0);
    assert(*(sb + 1) == '\0');
}

static void test_set_fv_buffer_one_format_zero_argv_none() {
    char sb[] = { '0', '\0' };
    char format[] = { '\0' };
    string_set(sb, sizeof sb, format);

    assert((sizeof sb) == 2);
    assert(strlen(sb) == 0);
    assert(*(sb + 1) == '\0');
}

static void test_set_fv_buffer_zero_format_zero_argv_none() {
    char sb[] = { '\0' };
    char format[] = { '\0' };
    string_set(sb, sizeof sb, format);

    assert((sizeof sb) == 1);
    assert(strlen(sb) == 0);
    assert(*(sb) == '\0');
}

static void test_set_fv_buffer_zero_format_one_argv_none() {
    char sb[] = { '\0' };
    char format[] = { '0', '\0' };
    int rv = string_set(sb, sizeof sb, format);

    assert(rv != 0);
    assert((sizeof sb) == 1);
    assert(strlen(sb) == 0);
    assert(*(sb) == '\0');
}

static void test_set_fv_buffer_some_format_some_argv_one() {
    char sb[] = { '0', '\0' };
    char format[] = { '%', 'd', '\0' };
    int rv = string_set(sb, sizeof sb, format, 1);

    assert(rv == 0);
    assert((sizeof sb) == 2);
    assert(strlen(sb) == 1);
    assert(*(sb) == '1');
}

int main(int argc, char **argv) {
    test_set_s_buffer_zero_source_null();
    test_set_s_buffer_one_source_one();
    test_set_s_buffer_zero_source_one();
    test_set_s_buffer_some_source_one();
    test_set_s_buffer_one_source_some();
    test_set_fv_buffer_zero_format_null_argv_none();
    test_set_fv_buffer_one_format_null_argv_none();
    test_set_fv_buffer_one_format_zero_argv_none();
    test_set_fv_buffer_zero_format_zero_argv_none();
    test_set_fv_buffer_zero_format_one_argv_none();
    test_set_fv_buffer_some_format_some_argv_one();
}

