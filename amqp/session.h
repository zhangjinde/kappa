/* session interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SESSION_H
#define SESSION_H

/* An AMQP session interface's structures and functions. */

#include <stdio.h>

/* An AMQP session structure. */
struct session {
};

/* Allocates a session.
On success, returns a pointer to a session, otherwise NULL. */
struct session* session_new();

/* Deallocates a session.
session: a previously allocated session. */
void session_free(struct session* session);

#endif

