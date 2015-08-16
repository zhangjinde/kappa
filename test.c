/*
* test structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "test.h"

static const char *STATS = "\nSTATISTICS\n\n%d TESTS\n%d ASSERTIONS\n%d PASSED\n%d FAILED\n\n";
static const char *PASS = "PASS";
static const char *FAIL = "FAIL";
static const int MAX_LENGTH = 256;
static struct test_attr test_attr;
static struct test_stat test_stat;

static void assertion_write(const struct test_assertion *assertion) {
    const char *result = assertion->truth ? PASS : FAIL;
    char *message = malloc(MAX_LENGTH);
    snprintf(message, MAX_LENGTH, assertion->description, assertion->actual, assertion->expected);
    test_message_create(message, MAX_LENGTH, assertion);
    fprintf(test_attr.out, "%s %s\n", result, message);
    free(message);
}

static void ixture_write(const struct test_fixture *fixture) {
    static struct test_fixture *current = NULL;
    if(!current || strcmp(current->description, fixture->description)) {
        fprintf(test_attr.out, fixture->description);
        fprintf(test_attr.out, "\n\n");
        current = (struct test_fixture *)fixture;
    }
}

static void stat_update(int truth) {
    ++test_stats.tests;
    ++test_stats.assertions;
    test_stats.failures += truth ? 0 : 1;
}

void test_recap() {
    fprintf(test_attr.out, STATS,
        test_stats.tests,
        test_stats.assertions, 
        test_stats.tests - test_stats.failures,
        test_stats.failures);
}

void test_assert(const struct test_fixture *fixture, const struct test_assertion *assertion) {
    test_stats_update(assertion->truth);
    test_fixture_write(fixture);
    test_assertion_write(assertion);
}

int main(int argc, char[] *argv) {
    void *handle;
    void (*test_exec)();
    handle = dlopen("...", RTLD_NOW);
    if(!handle) {
        fprintf(stderr, "error %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    *(void **)(&test_exec) = dlsym(handle, "test_exec");
    char *error;
    if((error = dlerror()) != NULL) {
        fprintf(stderr, "error %s\n", error);
        exit(EXIT_FAILURE);
    }
    (*test_exec)();
    dlclose(handle);
    exit(EXIT_SUCCESS);
}

