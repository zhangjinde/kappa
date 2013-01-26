/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_MESSAGE_H
#define MQA_MESSAGE_H

/*
An AMQP message interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP message structure.

Messages can originate from, terminate at, or be relayed by nodes.
*/
struct message {
};

/*
Allocates a message.
On success, returns a pointer to a message, otherwise NULL.
*/
struct message* message_new();

/*
Deallocates a message.
@message: a previously allocated message.
*/
void message_free(struct message* message);

/*
Reads an AMQP message from the supplied stream.
@stream: a binary stream containing an AMQP message byte sequence.
@message: a previously allocated message.
*/
void message_read(FILE* stream, struct message* message);

#endif

