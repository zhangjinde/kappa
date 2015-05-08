#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

static void swap(int *const vector, long x, long y) {
    int z = *(vector + x);

    *(vector + x) = *(vector + y);
    *(vector + y) = z;
}

static void sort(int *const vector, size_t size) {
    size_t i, u = size;
    int *const v = vector, *l, *r;

    for(l = v, r = v + u - 1; r - l >= 2; ++l, --r, u -= 2) {
        for(i = 0; i < u; ++i) {
            if(*(l + i) > *r) swap(v, r - v, l + i - v);
            if(*(r - i) < *l) swap(v, l - v, r - i - v);
        }
    }
}

int main(void) {
    int vector[] = { 5, 7, 8, 6, 4, 9, 0, 2, 3, 1 };
    size_t i, size = sizeof vector / sizeof(int);

    sort(vector, size);

    printf("size %li\n", size);
    for(i = 0; i < size; i++) {
        printf(i == size - 1 ? "%d\n" : "%d ", *(vector + i));
    }

    return 0;
}

