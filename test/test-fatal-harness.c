/*
* a harness for fatal test routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "kappa/log.h"
#include "kappa/fatal.h"
#include "kappa/error.h"
#include "kappa/trace.h"
#include "kappa/debug.h"

static void terminate(void) {
    trace("terminated a process");
}

int main(int argc, const char **argv) {
    assert(argc == 1);

    const char *mod_name;

    mod_name = argv[0];
    log_init(mod_name);

    if (atexit(terminate))
        error("a termination handler could not be registered, [%s]", mod_name);

    errno = 1;
    fatal("testing a fatal condition");
    
    assert(0);
}

