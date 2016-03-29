/* terminus interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_TERMINUS_H
#define MQA_TERMINUS_H

/* An AMQP terminus interface's structures and functions. */

#include <stdio.h>

/* An AMQP terminus structure.
A terminus is a unidirectional route between two nodes.
A terminus is responsible for tracking the state of a particular stream of
incoming or outgoing messages. */
struct terminus {
};

/* Allocates a terminus.
On success, returns a pointer to a terminus, otherwise NULL. */
struct terminus* terminus_new();

/* Deallocates a terminus.
terminus: a previously allocated terminus. */
void terminus_free(struct terminus* terminus);

#endif

