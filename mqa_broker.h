/* broker interface
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_BROKER_H
#define MQA_BROKER_H

/* An AMQP broker interface's structures and functions. */

#include <stdio.h>

/* An AMQP broker structure. */
struct broker {
};

/* Allocates a broker.
On success, returns a pointer to a broker, otherwise NULL. */
struct broker* broker_new();

/* Deallocates a broker.
broker: a previously allocated broker. */
void broker_free(struct broker* broker);

#endif

