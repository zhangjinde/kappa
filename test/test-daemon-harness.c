/*
* a harness for daemon tests routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "kappa/notused.h"
#include "kappa/log.h"
#include "kappa/fatal.h"
#include "kappa/error.h"
#include "kappa/trace.h"
#include "kappa/debug.h"
#include "kappa/signal.h"
#include "kappa/daemon.h"

int main(int argc, const char **argv) {
    int e;
    pid_t test_pid;
    const char *mod_name, *sem_name;

    mode_t sem_mode = S_IRUSR | S_IWUSR;
    unsigned sem_init_value = 0;
    unsigned sem_flag = O_CREAT;
    sem_t *sem = NULL;

    mod_name = argv[0];

    log_init(mod_name);

    if (argc != 3)
        fatal("missing semaphore name [%s] and/or test pid [%s], [%s]",
            argv[1], argv[2], mod_name);

    sem_name = argv[1];
    test_pid = atoi(argv[2]);

    if (make_daemon(0, 0))
        fatal("making a daemon [%s] failed", mod_name);

    if (kill(test_pid, SIGUSR1))
        fatal("sending a signal [%d] to a process [%d] failed, [%s]",
            SIGUSR1, test_pid, mod_name);

    if ((sem = sem_open(sem_name, sem_flag, sem_mode, sem_init_value)) == SEM_FAILED)
        fatal("opening a semaphore [%s] failed, [%s]", sem_name, mod_name);

    while ((e = sem_wait(sem)) < 0)
        if (errno != EINTR)
            fatal("waiting on a semaphore [%s] failed, [%s]", sem_name, mod_name);

    trace("a semaphore [%s] unlocked, [%s]", sem_name, mod_name);

    if (sem_close(sem) == -1)
        error("closing a semaphore [%s] failed, [%s]", sem_name, mod_name);

    log_deinit(mod_name);

    exit(EXIT_SUCCESS);
}

