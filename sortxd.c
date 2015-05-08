#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <pthread.h>

static const int maxlen = INT_MAX;

static void output(const int *v, int n) {
    int i;

    for (i = 0; i < n; i++)
        printf(i == n - 1 ? "%d\n" : "%d ", *(v + i));
}

static void swap(int *v, int i, int j) {
    int t;
    
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static void sort(int *v, int n) {
    int i, j, k, l, m;
/*
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
*/

    printf("\nlen %d sqrt %f\n", n, sqrt(n));

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

static int read(int *v, int n) {
    int i;

    for (i = 0; i < n && scanf("%d", v + i) == 1; i++)
        ;
    return i;
}

int main(void) {
    int n;
    int *v = (int *)malloc(maxlen * sizeof(int));

    n = read(v, maxlen);
    sort(v, n);
    output(v, n);

    free(v);
    exit(0);
}

