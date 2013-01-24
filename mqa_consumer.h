/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_CONSUMER_H
#define MQA_CONSUMER_H

/*
An AMQP consumer interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP consumer structure.

Named entities responsible for the safe storage and/or delivery of messages.
Messages can originate from, terminate at, or be relayed by consumers.
*/
struct consumer {
};

/*
Allocates a consumer.
On success, returns a pointer to a consumer, otherwise NULL.
*/
struct consumer* consumer_new();

/*
Deallocates a consumer.
@link: a previously allocated consumer.
*/
void consumer_free(struct consumer* consumer);

#endif

