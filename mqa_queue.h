/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_QUEUE_H
#define MQA_QUEUE_H

//TODO: use klt43 library @ https://github.com/fakhrazeyev/klt43

/*
An AMQP queue interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP queue structure.

A queue store and forward messages.
*/
struct queue {
};

/*
Allocates a queue.
On success, returns a pointer to a queue, otherwise NULL.
*/
struct queue* queue_new();

/*
Deallocates a queue.
@link: a previously allocated queue.
*/
void queue_free(struct queue* queue);

#endif

