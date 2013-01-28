/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_TERMINUS_KIND_H
#define MQA_TERMINUS_KIND_H

/*
The AMQP terminus kind enumeration.

There are two kinds of terminus: sources and targets. A terminus is responsible
for tracking the state of a particular stream of incoming or outgoing messages.
*/
enum terminus_kind {
    /* A source tracks outgoing messages. */
    source,

    /* A target tracks incoming messages. */
    target
};

#endif

