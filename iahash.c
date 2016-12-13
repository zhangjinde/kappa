/* hash utility routines
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Theta. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define error(s)\
    fprintf(\
        stderr, "e: %s, n: %d, s: [%s], f: %s, l: %d\n", \
        s, errno, strerror(errno), __FILE__, __LINE__\
    )\

/* (sqrt(5)-1)/2

[0] Donald E. Knuth. Sorting and Searching, volume 3 of The Art of Computer
Programming. Addison-Wesley, 1998. 2nd ed.

[1] Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein,
Clifford. Introduction to Algorithms. The MIT Press, 2009. 3rd ed. */
#define A 0.6180339887498949

static unsigned mhashi(int i, int n) {
    unsigned h;
    unsigned long w, p, s, r, ra, rb;

    w = sizeof(int) * 8;
    p = (unsigned long)(ceil(log2(n)));
    s = (unsigned long)(A * pow(2, w));
    r = (unsigned)i * s;
    ra = r >> w;
    rb = r ^ (ra << w);
    h = (unsigned)(rb >> (w-p));

    return h;
}

int main(int argc, char *argv[]) {
    int i, n, na, *v;

    n = argc-1;
    if (!(v = (int *)malloc((size_t)n * sizeof(int)))) {
        error("memop failed");
        exit(1);
    }

    for (i = 1; i<=n; i++)
        v[i-1] = atoi(argv[i]);

    na = n<256 ? 256 : n;
    for (i = 0; i<n; i++)
        printf(i<n-1 ? "%d " : "%d\n", mhashi(v[i], na));

    exit(0);
}

#undef error
#undef A

