/* buffer structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef BUFFER_H
#define BUFFER_H

struct buffer {
    unsigned char *head;
    unsigned char *cursor;
};

struct buffer *buffer_new(); 
void buffer_write(struct buffer *buffer, const unsigned char *message, ...);
int buffer_size(const struct buffer *buffer);
void buffer_reset(struct buffer *buffer);
void buffer_free(struct buffer *buffer);

#endif

