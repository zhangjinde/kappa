/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_FRAME_H
#define MQA_FRAME_H

/*
An AMQP frame interface's structures and functions.
*/

#include <stdio.h>

/*
An AMQP frame structure.
*/
struct frame {
};

/*
Allocates a frame.
On success, returns a pointer to a frame, otherwise NULL.
*/
struct frame* frame_new();

/*
Deallocates a frame.
@link: a previously allocated frame.
*/
void frame_free(struct frame* frame);

#endif

