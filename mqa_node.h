/* note interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_NODE_H
#define MQA_NODE_H

/* An AMQP node interface's structures and functions. */

#include <stdio.h>

/* An AMQP node structure.
Named entities responsible for the safe storage and/or delivery of messages.
Messages can originate from, terminate at, or be relayed by nodes. */
struct node {
};

/* Allocates a node.
On success, returns a pointer to a node, otherwise NULL.  */
struct node* node_new();

/* Deallocates a node.
note: a previously allocated node. */
void node_free(struct node* node);

#endif

