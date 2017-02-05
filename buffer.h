/*
* buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef BUFFER_H
#define BUFFER_H

struct buffer {
    unsigned char *head;
    unsigned char *cursor;
};

struct buffer *buffer_new(); 
void buffer_write(struct buffer *, const unsigned char *msg, ...);
int buffer_size(const struct buffer *);
void buffer_reset(struct buffer *);
void buffer_free(struct buffer *);

#endif
/*
* string buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef SBUFFER_H
#define SBUFFER_H

int sbuffer_set(char *bf, size_t nb, const char *fmt, ...);
int sbuffer_copy(char *bf, size_t nb, const char *src);

#endif

