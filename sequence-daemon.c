/*
* sequence daemon
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include "log.h"
#include "error.h"
#include "fatal.h"
#include "trace.h"
#include "sequence.h"

static const char *module = "sequence-daemon";

void terminate(void) {
    trace("module %s terminated", module);
}

int main(int argc, const char **argv) {
    int e;
    sequence_t *sequence;

    const char *host = "127.0.0.1";
    unsigned short port = 64000;
    unsigned short queue = 8;

    log_init(module);

    trace("module %s is starting up", module);

    if ((e = atexit(terminate)))
        fatal("module %s termination handler could not be registered", module);

    if ((e = sequence_create(&sequence, host, port, queue)))
        fatal("module %s start up failed", module);

    exit(EXIT_SUCCESS);
}

