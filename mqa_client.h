/* client interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_CLIENT_H
#define MQA_CLIENT_H

/* An AMQP client interface's structures and functions. */

#include <stdio.h>

/* An AMQP client structure. */
struct client {
};

/* Allocates a client.
On success, returns a pointer to a client, otherwise NULL. */
struct client* client_new();

/* Deallocates a client.
client: a previously allocated client. */
void client_free(struct client* client);

#endif

