/*
* list structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "kappa/list.h"

struct  list_tuple {
    void *object;
    struct list_tuple *next;
};

struct list {
    int length;
    struct list_tuple *head;
    struct list_tuple *tail;
    void (* destroy)(void *object);
};

static int list_tuple_alloc(struct list_tuple **tuple) {
    if (!(*tuple = malloc(sizeof(struct list_tuple))))
        return error();
    return 0;
}

static int list_init(
    struct list *list,
    const struct list_attr *attr
) {
    list->length = 0;
    list->head = list->tail = NULL;
    list->destroy = attr && attr->destroy ? attr->destroy : NULL;
    return 0;
}

static int list_alloc(struct list **list) {
    if (!(*list = malloc(sizeof(struct list))))
        return error();
    return 0;
}

struct list_tuple *list_next(
    const struct list *list,
    const struct list_tuple *tuple
) {
    return tuple->next;
}

void *list_object(
    const struct list *list,
    const struct list_tuple *tuple
) {

}

int list_is_tail(
    const struct list *list,
    const struct list_tuple *tuple
) {

}

int list_is_head(
    const struct list *list,
    const struct list_tuple *tuple
) {

}

struct list_tuple *list_tail(const struct list *list) {
}

struct list_tuple *list_head(const struct list *list) {
}

int list_length(const struct list *list) {
}

int list_remove(
    struct list *list,
    const struct list_tuple *tuple,
    void **object
) {

}

int list_insert(
    struct list *list,
    struct list_tuple *tuple,
    const void *object
) {
    struct list_tuple *t;

    list_tuple_alloc(&t);
    t->object = (void *)object;

    t->next = !list->length ? NULL : tuple ? tuple->next : list->head;
    list->head = !list->length ? t : !tuple ? t : list->head;

    if(tuple)
        tuple->next = t;

    ++list->length;

    return 0;
}

int list_destroy(struct list **list) {
    struct list_tuple *t, *u;

    if (*list && (*list)->destroy)
        for (t = (*list)->head; t; t = u) {
            u = t->next;
            (*list)->destroy(t);
        }

    free(*list);

    memset(*list, 0, sizeof(struct list));
    *list = NULL;

    return 0;
}

int list_create(struct list **list, const struct list_attr *attr) {
    int e;

    if ((e = list_alloc(list))
        return error(e);

    if ((e = list_init(*list, attr))
        return error(e);

    return 0;
}

