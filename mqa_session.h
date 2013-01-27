/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_SESSION_H
#define MQA_SESSION_H

/*
An AMQP session interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP session structure.
*/
struct session {
};

/*
Allocates a session.
On success, returns a pointer to a session, otherwise NULL.
*/
struct session* session_new();

/*
Deallocates a session.
@link: a previously allocated session.
*/
void session_free(struct session* session);

#endif

