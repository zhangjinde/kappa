/* error utility routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef ERROR_H
#define ERROR_H

#define ensure(value, ...) if(!value) err((args){__VA_ARGS__})

#define error(s)\
    fprintf(\
        stderr, "e: %s, n: %d, s: [%s], f: %s, l: %d\n", \
        s, errno, strerror(errno), __FILE__, __LINE__\
    )\

typedef struct args {
    void (*func)(void *);
    void *arg;
    char const *format;
    char const *message;
} args;

void fail(void *);
void null(void *);
void err(args);
char *format(char const *format_info, ...);
void concat(char **target, char const *source);
void error(int quit, const char *message, ...);

#endif

