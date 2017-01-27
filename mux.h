/*
* multiplexing structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef MUX_H
#define MUX_H

enum mux_func_type {
    mux_func_read,
    mux_func_write
};

struct mux_func {
    enum mux_func_type type;
    int fd;
    int is_active;
    void (* func)(struct mux_func *);
};

void mux(struct mux_func **funcs);

#endif

