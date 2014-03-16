/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_ERRORS_H
#define SIO_ERRORS_H

enum {
    unknown,
    stream_close_failed,
    stream_seek_failed,
    stream_tell_failed,
    file_open_failed,
    file_remove_failed,
    bytes_discarded
};

#endif

