/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_FORMAT_H
#define MQA_FORMAT_H

/*
The AMQP Format Code structures and functions.
*/
struct format {
    enum format_category category;
};

/*
Allocates a format code.
On success, returns a new format code, otherwise NULL.
*/
struct format* format_new();

/*
Deallocates a previously allocated format code.
@format: a previously allocated format code.
*/
void format_free(struct format* format);

/*
Reads a format code from a stream.
@stream:
@format:
*/
void format_read(FILE* stream, struct format* format);

/*
Writes a format code into the supplied output stream.
@stream: a binary output stream.
@format:
*/
void format_write(FILE* stream, struct format* format);

#endif

