/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_CONNECTION_H
#define MQA_CONNECTION_H

/*
An AMQP connection interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP connection structure.
*/
struct connection {
};

/*
Allocates a connection.
On success, returns a pointer to a connection, otherwise NULL.
*/
struct connection* connection_new();

/*
Deallocates a connection.
@link: a previously allocated connection.
*/
void connection_free(struct connection* connection);

#endif

