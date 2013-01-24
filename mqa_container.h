/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_CONTAINER_H
#define MQA_CONTAINER_H

/*
An AMQP container interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP container structure.

A container holds nodes.
*/
struct container {
};

/*
Allocates a container.
On success, returns a pointer to a container, otherwise NULL.
*/
struct container* container_new();

/*
Deallocates a container.
@container: a previously allocated container.
*/
void container_free(struct container* container);

#endif

