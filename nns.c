#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

enum limits {
    max_array_size = 1024
};

static int seek(const int *vector, int size, double mean) {
    assert(vector);
    assert(size);

    int *origin = (int *)vector;
    int index = -1;
    double min_dev = -1;

    while(size--) {
        double dev = fabs(*vector++ - mean);
        if(min_dev < 0 || dev < min_dev) {
            index = vector - origin - 1;
            min_dev = dev;
        }
    }

    assert(index != -1);
    return index;
}

static double calc(const int *vector, int size) {
    assert(vector);
    assert(size);

    double sum = 0;
    for(int index = size; index > 0; index--, vector++)
        sum += *vector;

    return (sum / size);
}

static int read(int *vector) {
    assert(vector);

    int item;
    int size;
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

    int size = read(vector);
    if(!size) {
        fprintf(stderr, "invalid input\n");
        exit(1);
    }
    assert(size);

    double mean = calc(vector, size);
    int index = seek(vector, size, mean);

    assert(index != -1);
    printf("%d\n", vector[index]);

    return 0;
}

