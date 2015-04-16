#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

enum limits {
    max_array_size = 1024
};

static int compare(const int *x, const int *y) {
    return
        *x < *y ? -1 :
        *x == *y ? 0 :
        1;
}

static long contains(long key, int *vector, size_t size) {
    int *status = (int *)bsearch(
        &key,
        vector,
        size,
        sizeof (int),
        (int (*)(const void *, const void *))compare
    );
    return status ? 1 : 0;
}

static int seek(int *vector, size_t size, int target) {

    int *block = (int *)malloc(size * sizeof (int));
    int *block_o = block;
    size_t block_s = 0;

    int *vector_o = vector;
    size_t vector_s = size;

    while((size_t)(vector - vector_o) < vector_s) {
        int *x = vector++;
        int *y = x + 1;
        for( ; (size_t)(y - vector_o) < vector_s; y++) {
            int xi = (int)(x - vector_o);
            int yi = (int)(y - vector_o);
            if(
                *x + *y == target && 
                !contains(xi, block, block_s) &&
                !contains(yi, block, block_s)
            ) {

                printf("%d %d\n", *x, *y);
                *block++ = xi;
                *block++ = yi;
                block_s += 2;
                break;
            }
        }
    }
    free(block_o);
    return 0;
}

static int sort(int *vector, size_t size) {
    qsort(vector, size, sizeof (int), (int (*)(const void *, const void *))compare);
    return 0;
}

static size_t read(int *vector) {
    assert(vector);

    int item;
    size_t size;
    for(size = 0; (scanf("%d", &item)) == 1; ) {
        if(++size > max_array_size) {
            --size;
            fprintf(stderr, "warning: threshold %d elements\n", max_array_size);
            break;
        }
        *vector++ = item;
    }

    return size;
}

int main(void) {

    int vector[max_array_size] = { 0 };
    int status = -1;

    size_t size = read(vector);
    if(!size) {
        fprintf(stderr, "invalid input\n");
        exit(1);
    }
    assert(size);

    int target = vector[--size];
    status = sort(vector, size);
    status = seek(vector, size, target);

    return status;
}

