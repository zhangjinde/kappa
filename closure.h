/*
* closure utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef CLOSURE_H
#define CLOSURE_H

struct closure {
    void **argv;
    int (* func)(struct closure *);
};

#endif

