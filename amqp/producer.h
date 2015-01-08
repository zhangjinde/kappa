/* producer interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef PRODUCER_H
#define PRODUCER_H

/*
An AMQP producer interface's structures and functions. */

#include <stdio.h>

/* An AMQP producer structure. */
struct producer {
};

/* Allocates a producer.
On success, returns a pointer to a producer, otherwise NULL. */
struct producer* producer_new();

/* Deallocates a producer.
producer: a previously allocated producer. */
void producer_free(struct producer* producer);

#endif

