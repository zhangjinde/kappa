/*
* file stream library of structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <errno.h>
#include "kappa/error.h"
#include "kappa/file.h"

static int file_close(FILE *stream) {
    if (stream && fclose(stream))
        return error("closing a file stream failed");

    return 0;
}

int file_remove(const char *path) {
    if (remove(path))
        return error("removing a file [%s] failed", path);

    return 0;
}

int file_create(const char *path, FILE **stream) {
    const char *mode = "w+b";

    if (!(*stream = fopen(path, mode))) {
        (void)file_close(*stream);
        return error("creating a file [%s] with mode [%s] failed", path, mode);
    }

    return 0;
}

int file_is_empty(const char *path) {
    int e;
    FILE *stream = NULL;
    const char *mode = "rb";

    if (!(stream = fopen(path, mode))) switch(errno) {
    case ENOENT:
        (void)file_close(stream);
        return error("a file [%s] does not exist", path);
    default:
        (void)file_close(stream);
        return error("opening a file [%s] with mode [%s] failed", path, mode);
    }

    if (fseek(stream, 0, SEEK_END)) {
        (void)file_close(stream);
        return error("seeking to the end of the stream [%s] failed", path);
    }

    if ((e = ftell(stream)) < 0) {
        (void)file_close(stream);
        return error("obtaining a position for stream [%s] failed", path);
    }

    (void)file_close(stream);
    return e ? 0 : 1;
}

int file_exists(const char *path) {
    FILE *stream = NULL;
    const char *mode = "rb";

    if (!(stream = fopen(path, mode))) switch(errno) {
    case ENOENT:
        return 0;
    default:
        file_close(stream);
        return error("opening a file [%s] with mode [%s] failed", path, mode);
    }

    return 1;
}

