/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_ERROR_TYPE_H
#define SIO_ERROR_TYPE_H

struct error_type {
    int value;
    const char *string;
};

const struct error_type const *(* get_error_type)(int error_id);

#endif

