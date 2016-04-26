#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

#define hashsize 101

struct list {
    int value;
    int flag;
    struct list *next;
};

static struct list *hashtab[hashsize];

static unsigned dhashi(int i) {
    return (unsigned)i* (unsigned)A % hashsize;
}

static struct list *lookup(int value) {
    struct list *x = NULL;

    for (x = hashtab[dhashi(value)]; x; x = x->next)
        if (x->value == value)
            return x;

    return NULL;
}

static struct list *install(int value) {
    struct list *x = NULL;
    unsigned h;

    if (!(x = lookup(value)))
        x = (struct list *)malloc(sizeof(*x));

    h = dhashi(value);
    x->value = value;
    x->flag = 0;
    x->next = hashtab[h];
    hashtab[h] = x;

    return x;
}

static void stats(int *v, int n) {
    int i;
    printf("size: %d\n", n);
    for (i = 0; i < n; i++)
        printf(i == n-1 ? "%d\n" : "%d ", v[i]);
}

static void swap(int *v, int i, int j) {
    int t;
    if (!v) { error("null vec"); exit(1); }
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

static void compute(int *v, int n) {
    int i, j, k, l, ri, ra, rb, rn;
    if (!v) { error("null vec"); exit(1); }
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
        {  error("memop failed"); exit(1); }

    for (l = 0; (n = scanf("%d", &o)) == 1 && n != EOF; l++) {
        if (l == c-1) {
            if (!(u = realloc(*v, (size_t)(s*2)))) {
                free(*v);
                error("memop failed");
                exit(1);
            }
            *v = u;
        }
        *(*v+l) = o;
    }
    return l;
}

int main(void) {
    int i, n, *v;
    struct list *ve;

    if (!(n = readv(&v))) {
        free(v);
        error("read failed");
        exit(1);
    }
    assert(v);

    compute(v, n);
    stats(v, n);

    for (i = 0; i<n; i++) {
        if (!(ve = lookup(v[i])))
            ve = install(v[i]);
        ve->flag++;
    }

    for (i = 0; i<hashsize; i++)
        for (ve = hashtab[i]; ve; ve = ve->next)
            printf("%d: %d\n", ve->value, ve->flag);
    
    free(v);
    exit(0);
}

