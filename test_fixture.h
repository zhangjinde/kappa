/* test fixture structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef TEST_FIXTURE_H
#define TEST_FIXTURE_H

struct fixture_attr {
    FILE *out;
};

struct fixture_stats {
    int tests;
    int assertions;
    int failures;
};

enum fixture_value_type {
    TEST_VALUE_NUMBER,
    TEST_VALUE_STRING
};

struct fixture_result {
    enum fixture_value_type type;
    union {
        int number;
        const char *string;
    } value;
};

struct fixture_assertion {
    int truth;
    const char *desc;
    struct fixture_result actual;
    struct fixture_result expected;
};

struct fixture {
    const char *desc;
};

/* writes out the statistics for the tests */
void fixture_recap();

/* tests assertions and wries out the results for each
fixture: a fixture of the assert
assertion: an assertion to test */
void fixture_assert(const struct fixture *fixture, const struct fixture_assert *assert);

void fixture_init();

#endif

