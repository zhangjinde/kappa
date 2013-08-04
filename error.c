/* error utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "trace.h"
#include "error.h"

static const size_t MESSAGE_MAX_LENGTH = 256;
static const char *ARGUMENT_NULL = "Null is not a valid value.\n";

static void error_trace(const char *message, va_list varg) {
    char string[MESSAGE_MAX_LENGTH];
    vsnprintf(string, sizeof(string), message, varg);
    trace(string);
}

void error(int quit, const char *message, ...) {
    va_list vargs;
    va_start(vargs, format);
    error_trace(format, vargs);
    va_end(vargs);
    if(quit == 1) exit(EXIT_FAILURE);
}

void fail(void *args) {
    abort();
}

void null(void *args) {
    fprintf(stderr, "%s", ARGUMENT_NULL);
    fail(args);
}

void err(args args) {
    if(args.message) fprintf(stderr, args.format ? args.format : "%s", args.message);
    if(args.func) args.func(args.arg);
}

char *format(char const *format, ...) {
    char *output;
    va_list list;
    va_start(list, format);
    size_t size = vsnprintf(NULL, 0, format, list) + 1;
    if((output = malloc(size)) == NULL) return(NULL);
    vsnprintf(output, size, format, list);
    va_end(list);
    return(output);
}

void concat(char **target, char const *source) {
    if(!source) { fprintf(stderr, "Null is not a valid value.\n"); exit(1); }
    if(*target) {
        char buffer[strlen(*target) + 1];
        strcpy(buffer, *target);
        free(*target);
        *target = malloc(strlen(buffer) + strlen(source) + 1);
        strcpy(*target, buffer);
        strcat(*target, source);
    } else {
        *target = malloc(strlen(source) + 1);
        strcpy(*target, source);
    }
}

