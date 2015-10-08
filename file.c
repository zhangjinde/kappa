/*
* file io wrapper utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "error.h"
#include "file.h"

static int file_close(struct closure *closure) {
    FILE *stream = *closure->argv;
    if (stream && (fclose(stream))) return error(stream_close_failed);
    return 0;
}

int file_exists(const char *path) {
    FILE *stream = NULL;
    const char *mode = "rb";
    struct closure finally = { .argv = (void *[]){ stream }, .func = finally_file_close };

    if (!(stream = fopen(path, mode))) switch(errno) {
        case ENOENT: return 0;
        default: return error(file_open_failed, path, mode);
    }

    finally.func(&finally);
    return 1;
}

int file_is_empty(const char *path) {
    int e;
    FILE *stream = NULL;
    const char *mode = "rb";
    struct closure finally = {
        .argv = (void *[]){ stream },
        .func = finally_file_close
    };

    if (!(stream = fopen(path, mode))) switch(errno) {
        case ENOENT: return 1;
        default: return error(file_open_failed, path, mode);
    }
    if ((fseek(stream, 0, SEEK_END))) return error_finally(&finally, stream_seek_failed, path);
    if ((e = ftell(stream)) < 0) return error_finally(&finally, stream_tell_failed, path);

    finally.func(&finally);
    return (e ? 0 : 1);
}

int file_create(const char *path) {
    FILE *stream = NULL;
    const char *mode = "w+b";
    struct closure finally = { .argv = (void *[]){ stream }, .func = finally_file_close };

    if (!(stream = fopen(path, mode))) return error(file_open_failed, path, mode);
    finally.func(&finally);
    return 0;
}

int file_remove(const char *path) {
    if ((remove(path))) return error(file_remove_failed, path);
    return 0;
}

