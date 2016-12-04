/* sort utility routines
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

static void error(const char *errm, int errn, const char *file, int line)
{
    fprintf(stderr, "%s, %s, file: %s, line: %d\n", errm, strerror(errn), file, line); 
    exit(1);
}

static void stats(int *v, int n)
{
    int i;

    printf("size: %d\n", n);
    for (i = 0; i < n; i++)
        printf(i == n-1 ? "%d\n" : "%d ", v[i]);
}

static void swap(int *v, int i, int j)
{
    int t;
    if (!v) error("null vec", 1, __FILE__, __LINE__);

    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static void compute(int *v, int n)
{
    int i, j;
    if (!v) error("null vec", 1, __FILE__, __LINE__);
    if (!(n >= 2)) return;

    for (i = 1; i < n; i++)
        for (j = i; j > 0; j--)
            if (v[j] < v[j-1])
                swap(v, j, j-1);
    
    stats(v, n);
}

static int readv(int **v)
{
    int o, n, l, *u;
    int c = 4096, s = c * (int)sizeof(int);

    if (!(*v = (int *)malloc((size_t)s)))
        error("memop failed", errno, __FILE__, __LINE__);

    for (l = 0; (n = scanf("%d", &o)) == 1 && n != EOF; l++) {
        if (l == c-1) {
            if (!(u = realloc(*v, (size_t)(s*2)))) {
                free(*v);
                error("memop failed", errno, __FILE__, __LINE__);
            }
            *v = u;
        }
        *(*v+l) = o;
    }
    return l;
}

int main(void)
{
    int n, *v;

    if (!(n = readv(&v))) {
        free(v);
        error("read failed", errno, __FILE__, __LINE__);
    }
    assert(v);

    compute(v, n);

    free(v);
    exit(0);
}

