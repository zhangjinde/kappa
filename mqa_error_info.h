/* error info interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_ERROR_INFO_H
#define MQA_ERROR_INFO_H

/* The AMQP Error Info interface's structures and functions. */

#include <stdio.h>

/* The AMQP Error Info structure. */
struct error_info {
    const char* name;
    const char* value;
};

#endif

