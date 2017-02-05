/*
* sequence structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef SEQUENCE_H
#define SEQUENCE_H

typedef struct sequence sequence_t;

int sequence_create(
    sequence_t **sequence,
    const char *host,
    unsigned short port,
    unsigned short queue
);

#endif

