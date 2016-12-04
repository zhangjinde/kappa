/* sort utility routines
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

static void error(const char *errm, int errn, const char *file, int line) {
    fprintf(stderr, "%s, %s, file: %s, line: %d\n", errm, strerror(errn), file, line); 
    exit(1);
}

static void stats(int *v, int n) {
    int i;
    printf("size: %d\n", n);
    for (i = 0; i < n; i++)
        printf(i == n-1 ? "%d\n" : "%d ", v[i]);
}

static void swap(int *v, int i, int j) {
    int t;
    if (!v) error("null vec", 1, __FILE__, __LINE__);
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static void compute(int *v, int n) {
    int i, j, k, l, ri, ra, rb, rn;
    if (!v) error("null vec", 1, __FILE__, __LINE__);
    if (!(n >= 2)) return;

    rn = ra = rb = 0;
    for (i = 0, j = n/2; i*i < n; i++, j = j<1 ? n/2:j/2) {
        for (k = n/2, ra = rb; k > 0; k /= 2, rb++, rn = rb-ra)
            for (l = rb-1; l>=ra && v[l+1]<v[l]; l--)
                swap(v, l, l+1);

        for (ri = i; ri>0; ri--)
            for (k = 0; k<rn; k++)
                if (v[ri*rn+k] < v[(ri-1)*rn+k])
                    swap(v, ri*rn+k, (ri-1)*rn+k);

        for (k = 1; k<=rn-1 && i>0; k++)
            for (l = 1; l<=k; l++)
                if (v[k+rn-l] < v[k])
                    swap(v, k+rn-l, k);
    }
}

static int readv(int **v) {
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

int main(void) {
    int n, *v;

    if (!(n = readv(&v))) {
        free(v);
        error("read failed", errno, __FILE__, __LINE__);
    }
    assert(v);

    compute(v, n);
    stats(v, n);

    free(v);
    exit(0);
}

