/*
* exploratory sort utility routines
* Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

static void error(const char *errm, int errn, const char *file, int line) {
    fprintf(stderr, "%s, %s, file: %s, line: %d\n", errm, strerror(errn), file, line); 
    exit(1);
}

static void stat(int *v, int n) {
    for (int i = 0; i < n; i++)
        printf(i == n-1 ? "%d\n" : "%d ", v[i]);
}

static void swap(int *v, int i, int j) {
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static void swap_l(int *const v, long i, long j) {
    int k = *(v + i);
    *(v + i) = *(v + j);
    *(v + j) = k;
}

static void sort_vn(int *v, int n) {
    if (!(n >= 2)) return;

    for (int i = 1; i < n; i++)
        for (int j = i; j > 0; j--)
            if (v[j] < v[j-1])
                swap(v, j, j-1);
    
    stat(v, n);
}

static void sort_vna(int *v, int n) {
    if (!(n >= 2)) return;
    int i, j, k, l, ri, ra, rb, rn;

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

static void sort_vnb(int *const v, size_t n) {
    size_t i, u = n;
    int *const v = v, *l, *r;

    for(l = v, r = v + u - 1; r - l >= 2; ++l, --r, u -= 2) {
        for(i = 0; i < u; ++i) {
            if(*(l + i) > *r) swap(v, r - v, l + i - v);
            if(*(r - i) < *l) swap(v, l - v, r - i - v);
        }
    }
}

static void sort_vnc(int *v, int n) {
    int i, j, k, l, m;
    k = 0;
    for (m = 0; m <= k; m++) {
        for (i = l = 0, j = n; i < n; j = j <= 2 ? n : j / 2, i++, l++) {
            printf("i j i-j k l %4d %4d %4d %4d %4d\n", i, j, j - i, k, l);
            if (j <= 2) {
                if (m == 0)
                    k++;
                l = -1;
                printf("\n");
            }
        }
    }

    k = 0;
    for (m = -1; m < k; m++) {
        m = m == -1 ? 0 : m;
        for (i = l = 0, j = n; i < n-1; j = j <= 2 ? n : j / 2, i++, l++) {
            printf("i j i-j k l %4d %4d %4d %4d %4d\n", i, j, j - i, k, l);

            for (j = i+1; j && v[j] < v[j-1]; j--) {
                printf("swap j j-1 (%4d %4d)\n", j, j-1);
                swap(v, j, j-1);
            }

            if (j <= 2) {
                if (m == 0)
                    k++;
                l = -1;
                printf("\n");
            }
        }
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

static int read_vn(int *v, int n) {
    int i;
    for (i = 0; i < n && scanf("%d", v + i) == 1; i++);
    return i;
}

int main(void) {
    int *v = (int *)malloc(maxlen * sizeof(int));
    int n = read(v, maxlen);
    sort(v, n);
    output(v, n);
    free(v);
    exit(0);
}

