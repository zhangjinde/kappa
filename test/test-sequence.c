/*
* tests for sequence routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "error.h"
#include "sequence.h"

/*
static int test_fetch_sequence(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e, fd;

    if (start_sequence(host, port, queue)) return 1;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if ((e = inet_pton(addr.sin_family, host, &addr.sin_addr)) != 1) return 1;

    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) return 1;
    if ((e = connect(fd, (struct sockaddr *)(&addr), sizeof addr))) return 1;

    char wbf[] = { 0x01 };
    ssize_t nbw = 0;
    int rbf[2] = { 0 };
    ssize_t nbr = 0;

    nbw = write(fd, wbf, sizeof wbf);
    assert(nbw == 1);

    nbr = read(fd, rbf, sizeof(int));
    assert(nbr == sizeof(int));

    nbw = write(fd, wbf, sizeof wbf); 
    assert(nbw == 1);

    nbr = read(fd, rbf+1, sizeof(int));
    assert(nbr == sizeof(int));
    assert(rbf[0] == rbf[1]-1);

    if ((e = close(fd))) return 1;

    return 0;
}
*/

static int test_sequence_create(
    const char *host,
    unsigned short port,
    unsigned short queue
) {
    int e;
    sequence_t *sequence;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    if ((e = pthread_mutex_init(&mutex, NULL))) return 1;
    if ((e = pthread_cond_init(&cond, NULL))) return 1;
    if (sequence_create(&sequence, host, port, queue)) return 1;
    for (;;) if ((e = pthread_cond_wait(&cond, &mutex))) return 1;
    free(sequence);
    return 0;
}

int main(void) {
    const char *host = "127.0.0.1";
    unsigned short port = 64000;
    unsigned short queue = 8;

    if (test_sequence_create(host, port, queue)) assert(0);
/*
    if (test_fetch_sequence(host, port, queue)) assert(0);
*/
    exit(EXIT_SUCCESS);
}

