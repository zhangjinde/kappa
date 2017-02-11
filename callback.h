/*
* callback structure
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef CALLBACK_H
#define CALLBACK_H

struct callback {
    void **argv;
    int (* func)(struct callback *);
};

#endif

