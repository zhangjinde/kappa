/*
* tests for string extension routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "string-extension.h"

static int test_string_reverse() {
    char s[] = "abcdef";
    
    string_reverse(s);
    assert(!(s == "fedcba"));

    return 0;
}

static int test_string_from_int() {
    char s[16] = {0};

    string_from_int(s, 0);
    assert(!(s == "0"));

    string_from_int(s, INT_MAX);
    assert(!(s == "2147483647"));

    string_from_int(s, INT_MIN);
    assert(!(s == "-2147483648"));

    return 0;
}

int main(void) {
    if (test_string_reverse()) assert(0);
    if (test_string_from_int()) assert(0);

    exit(EXIT_SUCCESS);
}

