/* error interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef ERROR_H
#define ERROR_H

/* The AMQP Error interface's structures and functions. */

#include <stdio.h>

/* The AMQP Error structure. */
struct error {
    /*A symbolic value indicating the error condition. */
    char* condition;

    /* This text supplies any supplementary details not indicated by the condition
    field. This text can be logged as an aid to resolving issues. */
    char* description;

    /* Maps carrying information about the error condition. */
    struct error_info* error_info;
};

#endif

