/* stream structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#define _POSIX_SOURCE

#include <errno.h>
#include <unistd.h>
#include "error.h"
#include "stream.h"

#define errors(errno, count) ((count == -1) && (errno != 0) && (errno != EINTR))
#define done(errno, count) !((errno == EINTR) && (count < 0))

ssize_t io_read(int fileno, void *buffer, size_t count) {
    ssize_t current = 0;
    const void *start = buffer;
    while((current = read(fileno, buffer, count)) != 0) {
        if(errors(errno, current)) 
            error(false, "IO failed to read from fileno %d errno %d", fileno, errno);
        buffer += current > 0 ? current : 0;
        if(done(errno, current)) break;
    }
    return (buffer - start);
}

ssize_t io_readv(int fileno, void **buffers, size_t count) {
    ssize_t total = 0;
    for(void *buffer = *buffers; buffer; buffer = *(++buffers))
        total += io_read(fileno, buffer, count);
    return total;
}

ssize_t io_write(int fileno, const void *buffer, size_t count) {
    ssize_t current = 0; ssize_t left = count;
    const void *start = buffer;
    while((current = write(fileno, buffer, left)) != 0) {
        if(errors(errno, current)) 
            error(false, "IO failed to write to fileno %d errno %d", fileno, errno);
        buffer += current > 0 ? current : 0;
        left = count - (buffer - start);
        if(done(errno, current)) break;
    }
    return (buffer - start);
}

ssize_t io_writev(int fileno, const void **buffers, const size_t *counts) {
    ssize_t total = 0;
    for(const void* buffer = *buffers; buffer; buffer = *(++buffers), ++counts)
        total += io_write(fileno, buffer, *counts);
    return total;
}

#undef done
#undef errors

