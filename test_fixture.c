/* buffer structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "fixture.h"

static const char *STATS = "\nSTATISTICS\n\n%d TESTS\n%d ASSERTIONS\n%d PASSED\n%d FAILED\n\n";
static const char *PASS = "PASS";
static const char *FAIL = "FAIL";
static const int MAX_LENGTH = 256;
static struct fixture_attr fixture_attr;
static struct fixture_stat fixture_stat;

static void fixture_message_create(char *message, size_t length, const struct fixture_assert *assert) {
    snprintf(message, length, assertion->description, assertion->actual, assertion->expected);
}

static void fixture_assert_write(const struct fixture_assertion *assertion) {
    const char *result = assertion->truth ? PASS : FAIL;
    char *message = malloc(MAX_LENGTH);
    fixture_message_create(message, MAX_LENGTH, assertion);
    fprintf(fixture_attr.out, "%s %s\n", result, message);
    free(message);
}

static void fixture_write(const struct fixture_fixture *fixture) {
    static struct fixture_fixture *current = NULL;
    if(!current || strcmp(current->description, fixture->description)) {
        fprintf(fixture_attr.out, fixture->description);
        fprintf(fixture_attr.out, "\n\n");
        current = (struct fixture_fixture *)fixture;
    }
}

static void fixture_stat_update(int truth) {
    ++fixture_stat.test;
    ++fixture_stat.asserts;
    fixture_stat.failures += truth ? 0 : 1;
}

void fixture_recap() {
    fprintf(fixture_attr.out, STATS,
        fixture_stat.tests,
        fixture_stat.asserts, 
        fixture_stat.tests - fixture_stats.failures,
        fixture_stat.failures);
}

void fixture_assert(const struct fixture *fixture, const struct fixture_assert *assert) {
    fixture_stat_update(assert->truth);
    fixture_fixture_write(fixture);
    fixture_assert_write(assert);
}

void fixture_init() {
    fixture_attr.out = stdout;
}

