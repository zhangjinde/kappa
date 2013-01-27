/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_PRODUCER_H
#define MQA_PRODUCER_H

/*
An AMQP producer interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP producer structure.
*/
struct producer {
};

/*
Allocates a producer.
On success, returns a pointer to a producer, otherwise NULL.
*/
struct producer* producer_new();

/*
Deallocates a producer.
@link: a previously allocated producer.
*/
void producer_free(struct producer* producer);

#endif

