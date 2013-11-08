/* multiplexing structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#define _POSIX_SOURCE

#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
#include "mux.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

struct mux_context {
    int highest;
    fd_set readers;
};

static void mux_init(struct mux_context *context, struct mux_func **funcs) {
    int highest = 0;
    for( ; *funcs && (highest = max(highest, (*funcs)->fileno)); funcs++);
    context->highest = highest + 1;
    FD_ZERO(&(context->readers));
}

static void mux_set(struct mux_context *context, struct mux_func **funcs) {
    for( ; *funcs; funcs++)
        if((*funcs)->active)
            FD_SET((*funcs)->fileno, &(context->readers));
}

static int mux_active(struct mux_func **funcs) {
    for( ; *funcs; funcs++)
        if((*funcs)->active)
            return 1;
    return 0;
}

void mux_mux(struct mux_func **funcs) {
    struct mux_context context;
    mux_init(&context, funcs);
    while(mux_active(funcs)) {
        mux_set(&context, funcs);
        select(context.highest, &(context.readers), NULL, NULL, NULL);
        for( ; *funcs; funcs++)
            if(FD_ISSET((*funcs)->fileno, &(context.readers)))
                (*funcs)->exec(*funcs);
    }
}

#undef max

