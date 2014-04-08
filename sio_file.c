/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "sio_error.h"
#include "sio_errors.h"
#include "sio_file.h"

static int finally_file_close(struct closure *closure) {
    assert(closure);
    assert(closure->argv);
    FILE *stream = *closure->argv;

    if(stream && (fclose(stream))) return error(stream_close_failed);
    return 0;
}

int file_exists(const char *url) {
    FILE *stream = NULL;
    const char *mode = "rb";

    struct closure finally = { .argv = (void *[]){ stream }, .func = finally_file_close };

    if(!(stream = fopen(url, mode))) switch(errno) {
        case ENOENT: return 0;
        default: return error(file_open_failed, url, mode);
    }

    finally.func(&finally);
    return 1;
}

int file_is_empty(const char *url) {
    FILE *stream = NULL;
    const char *mode = "rb";

    struct closure finally = { .argv = (void *[]){ stream }, .func = finally_file_close };

    int rv;
    if(!(stream = fopen(url, mode))) switch(errno) {
        case ENOENT: return 1;
        default: return error(file_open_failed, url, mode);
    }
    if((fseek(stream, 0, SEEK_END))) return error_finally(&finally, stream_seek_failed, url);
    if((rv = ftell(stream)) < 0) return error_finally(&finally, stream_tell_failed, url);

    finally.func(&finally);
    return (rv ? 0 : 1);
}

int file_create(const char *url) {
    FILE *stream = NULL;
    const char *mode = "w+b";

    struct closure finally = { .argv = (void *[]){ stream }, .func = finally_file_close };
    if(!(stream = fopen(url, mode))) return error(file_open_failed, url, mode);
    finally.func(&finally);
    return 0;
}

int file_remove(const char *url) {
    if((remove(url))) return error(file_remove_failed, url);
    return 0;
}

