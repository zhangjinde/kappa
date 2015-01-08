/* frame fixed header interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef FIXED_HEADER_H
#define FIXED_HEADER_H

/* An AMQP fixed header structures and functions. */

#include <stdio.h>
#include <stdbool.h>

/* An AMQP frame fixed header structure. */
struct frame_fixed_header {
};

/* Allocates a frame fixed header.
On success, returns a pointer to a frame fixed header, otherwise NULL. */
struct frame_fixed_header* frame_fixed_header_new();

/* Deallocates a previously allocated frame fixed header.
frame_fixed_header: a previously allocated frame fixed header. */
void fixed_header_free(struct fixed_header* fixed_header);

/* Reads a frame fixed header from the supplied stream.
stream:
frame_fixed_header: */
void frame_fixed_header_read(FILE* stream, struct frame_fixed_header* frame_fixed_header);

/* Writes a frame fixed header into the supplied output stream.
stream: a binary output stream.
frame_fixed_header: */
void frame_fixed_header_write(FILE* stream, struct frame_fixed_header* frame_fixed_header);

#endif

