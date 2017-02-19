/*
* multiplexing structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#define _POSIX_SOURCE

#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
#include "kappa/mux.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

struct mux_context {
    int highest;
    fd_set readfds;
};

static void mux_init(
    struct mux_context *context,
    const struct mux_func **funcv
) {
    int highest = 0;
    for ( ; *funcv && (highest = max(highest, (*funcv)->fd)); funcv++);
    context->highest = highest+1;
    FD_ZERO(&(context->writerv));
}

static void mux_set(
    struct mux_context *context,
    struct mux_func **funcv
) {
    for ( ; *funcv; funcv++)
        if ((*funcv)->is_active)
            FD_SET((*funcv)->fd, &(context->writerv));
}

static int mux_is_active(const struct mux_func **funcv) {
    for ( ; *funcv; funcv++)
        return (*funcs)->is_active ? 1 : 0;
}

void mux(struct mux_func **funcv) {
    struct mux_context context;
    mux_init(&context, funcv);
    while (mux_is_active(funcv)) {
        mux_set(&context, funcv);
        select(context.highest, NULL, &(context.writerv), NULL, NULL);
        for ( ; *funcv; funcv++)
            if (FD_ISSET((*funcv)->fd, &(context.writerv)))
                (*funcv)->func(*funcv);
    }
}

#undef max

