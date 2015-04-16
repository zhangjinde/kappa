#include <stdio.h>
#include <stdlib.h>

enum limits {
    max_array_size = 4096
};

static int read(int *vector, FILE *stream) {
    int size = 0;
    int value;
    while(fscanf(stream, "%d", &value) == 1) {
        ++size;
        *vector++ = value;
    }
    return size;
}

static int compare(const int *x, const int *y) {
    return
        *x < *y ? -1 :
        *x == *y ? 0 :
        1;
}

static int sort(int *vector, int size) {
    qsort(vector, size, sizeof (int), (int (*)(const void *, const void *))compare);
    return 0;
}

static int search(int key, int *vector, int size) {
    int *status = (int *)bsearch(
        &key,
        vector,
        size,
        sizeof (int),
        (int (*)(const void *, const void *))compare
    );
    return status ? (status - vector) : -1;
}

int main(int argc, char *argv[]) {
    int key = atoi(*++argv);
    int vector[max_array_size] = { 0 };

    int status = 0;

    int size = read(vector, stdin);
    status = sort(vector, size);
    status = search(key, vector, size);

    if(status >= 0) {
        printf("found key %d at index %d\n", *(vector + status), status);
    }

    return status;
}

