/* list routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

/* TODO: complete the list implementation */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "list.h"

/* allocates storage for a list tuple */
static int list_tuple_alloc(struct list_tuple **tuple) {
    if(!(*tuple = malloc(sizeof(struct list_tuple))))
        return(1);
    return(0);
}

/* initializes the list */
static int list_init(struct list *list, const struct list_attr *attr) {
    list->length = 0;
    list->head = list->tail = NULL;
    list->destroy = attr && attr->destroy ? attr->destroy : NULL;
    return(0);
}

/* allocates storage for the list */
static int list_alloc(struct list **list) {
    if(!(*list = malloc(sizeof(struct list))))
        return(1);
    return(0);
}

struct list_tuple *list_next(const struct list *list, const struct list_tuple *tuple) {
    return tuple->next;
}

void *list_object(const struct list *list, const struct list_tuple *tuple) {
}

int list_is_tail(const struct list *list, const struct list_tuple *tuple) {
}

int list_is_head(const struct list *list, const struct list_tuple *tuple) {
}

struct list_tuple *list_tail(const struct list *list) {
}

struct list_tuple *list_head(const struct list *list) {
}

int list_length(const struct list *list) {
}

int list_remove(struct list *list, const struct list_tuple *tuple, void **object) {
}

/* if the tuple is a NULL, a new tuple is inserted at head of the list */
int list_insert(struct list *list, struct list_tuple *tuple, const void *object) {
    struct list_tuple *new_tuple;
    list_tuple_alloc(&new_tuple);
    new_tuple->object = (void *)object;
    new_tuple->next = !list->length ? NULL
        : tuple ? tuple->next
        : list->head;
    list->head = !list->length ? new_tuple
        : !tuple ? new_tuple
        : list->head;
    if(tuple) tuple->next = new_tuple;
    ++list->length;
    return(0);
}

int list_destroy(struct list **list) {
    if(*list && (*list)->destroy)
        for(struct list_tuple *tuple = (*list)->head; tuple; tuple = tuple->next)
            (*list)->destroy(tuple);
    free(*list);
    memset(*list, 0, sizeof(struct list));
    *list = NULL;
    return(0);
}

int list_create(struct list **list, const struct list_attr *attr) {
    list_alloc(list);
    list_init(*list, attr);
    return(0);
}

