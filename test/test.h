/*
* test utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef TEST_H
#define TEST_H

void routine();

struct test_attr {
    FILE *out;
};

struct test_stat {
    int tests;
    int asserts;
    int failures;
};

enum test_value_type {
    TEST_VALUE_NUMBER,
    TEST_VALUE_STRING
};

struct test_result {
    enum test_value_type type;
    union {
        int number;
        const char *string;
    } value;
};

struct test_assertion {
    int truth;
    const char *desc;
    struct test_result actual;
    struct test_result expected;
};

struct test_fixture {
    const char *desc;
};

/*
* writes out the statistics for the tests
*/
void test_recap();

/*
* tests assertions and wries out the results for each
* fixture: a fixture of the assert
* assertion: an assertion to test
*/
void test_assert(const struct test_fixture *fixture, const struct test_assert *assert);

#endif

