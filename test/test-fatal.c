/*
* tests for fatal condition routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "kappa/log.h"
#include "kappa/fatal.h"
#include "kappa/error.h"
#include "kappa/trace.h"
#include "kappa/debug.h"

static void terminate(void) {
    trace("terminated a process");
}

static int test_fatal() {
    int e;
    const char *mod_name = __func__;
    const char *prog_name = "./test-fatal-harness";
    char shell_command[0x40] = { 0 };

    memmove(shell_command, prog_name, strlen(prog_name));
    debug("shell command text: [%s]", shell_command);

    log_init(mod_name);

    if (atexit(terminate))
        error("a termination handler could not be registered, [%s]", mod_name);

    e = system(shell_command);
    assert(e == 256);

    log_deinit(mod_name);

    return 0;
}

int main(void) {
    if (test_fatal()) assert(0);

    exit(EXIT_SUCCESS);
}

