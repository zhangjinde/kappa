/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_MODULE_H
#define SIO_MODULE_H

#include "sio_error.h"
#include "sio_errors.h"

enum {
    error_base = 0x0fa0
};

static struct error_type const errors[] = {
    [unknown] = { .value = error_base | unknown, .format = "unknown error" },
    [stream_close_failed] = { .value = error_base | stream_close_failed, .format = "failed to close a file stream %s" },
    [stream_seek_failed] = { .value = error_base | stream_seek_failed, .format = "failed to seek a file stream %s" },
    [stream_tell_failed] = { .value = error_base | stream_tell_failed, .format = "failed to obtain a position a file stream %s" },
    [file_open_failed] = { .value = error_base | file_open_failed, .format = "failed to open a file '%s' in mode %s" },
    [file_remove_failed] = { .value = error_base | file_remove_failed, .format = "failed to remove a file '%s'" },
    [bytes_discarded] = { .value = error_base | bytes_discarded, .format = "bytes discarded due to buffer limit" }
};

static struct error_type const *get_error(int error_id) {
    return &errors[error_id];
}

static struct error_type const *(* module_error)(int error_id) = &get_error;

static int error(int error_id) {
    return error_report(-1);
}

#endif

