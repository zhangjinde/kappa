/*
* buffer structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include "kappa/error.h"
#include "kappa/buffer.h"

struct buffer {
    void *base;
    void *ptr;
    size_t size;
};

void buffer_destroy(buffer_t *buffer) {
    free(buffer->base);
    free(buffer);
}

int buffer_create(buffer_t **buffer, size_t size) {
    buffer_t *b;

    if (!(b = (struct buffer *)malloc(sizeof(struct buffer))))
        return error("a memory region could not be allocated");

    if (!(b->base = malloc(sizeof(char) * size)))
        return error("a memory region could not be allocated");

    b->ptr = b->base;
    b->size = size;

    *buffer = b;
    return 0;
}

