/* link interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_LINK_H
#define MQA_LINK_H

/* An AMQP link interface's structures and functions. */

#include <stdio.h>

/* An AMQP link structure.
A link is a unidirectional route between two nodes. */
struct link {
};

/* Allocates a link.
On success, returns a pointer to a link, otherwise NULL. */
struct link* link_new();

/* Deallocates a link.
link: a previously allocated link. */
void link_free(struct link* link);

#endif

