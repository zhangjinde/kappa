/* connection interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef CONNECTION_H
#define CONNECTION_H

/* An AMQP connection interface's structures and functions. */

#include <stdio.h>

/* An AMQP connection structure. */
struct connection {
};

/* Allocates a connection.
On success, returns a pointer to a connection, otherwise NULL. */
struct connection* connection_new();

/* Deallocates a connection.
connection: a previously allocated connection. */
void connection_free(struct connection* connection);

#endif

