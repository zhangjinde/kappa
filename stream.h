/* stream structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef STREAM_H
#define STREAM_H

/* reads from a file descriptor to a buffer
fileno: a file descriptor to read from
buffer: a buffer to read to
count: a maximum number of bytes to read
On success, returns a number of bytes read */
ssize_t io_read(int fileno, void* buffer, size_t count);

/* reads from a file descriptor to buffers
fileno: a file descriptor to read from
buffers: buffers to read to
count: a maximum number of bytes to read
On success, returns a total number of bytes read */
ssize_t io_readv(int fileno, void** buffers, size_t count);

/* writes to a file descriptor from a buffer
fileno: a file descriptor to write to
buffer: a buffer to write from
count: a number of bytes to write
On success, returns a total number of bytes written
*/
ssize_t io_write(int fileno, const void* buffer, size_t count);

/* writes to a file descriptor from buffers
fileno: a file descriptor to write to
buffers: buffers to write from
counts: a number of bytes to write from each buffer
On success, returns a total number of bytes written */
ssize_t io_writev(int fileno, const void** buffers, const size_t* counts);

#endif

