/*
* list structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef LIST_H
#define LIST_H

struct list_attr {
    void (* destroy)(void *object);
};

typedef struct list_tuple list_tuple_t;
typedef struct list list_t;

/*
* obtains the element immediately following the specified element
*/
list_tuple_t *list_next(const struct list *, const struct list_tuple *);

/* 
* obtains the object stored in the element of the list
*/
void *list_object(const struct list *, const struct list_tuple *);

/*
* determines whether the element is at the tail of the list
*/
int list_is_tail(const struct list *, const struct list_tuple *);

/* 
* determines whether the element is at the head of the list. 
*/
int list_is_head(const struct list *, const struct list_tuple *);

/*
* obtains the tail element of the list
*/
struct list_tuple *list_tail(const struct list *);

/*
* obtains the head element of the list
*/
struct list_tuple *list_head(const struct list *);

/*
* determines a number of the elements in the list
*/
int list_length(const struct list *);

/*
* removes the element from the list
*
* list: the list from which the object will remove
* tuple: the tuple after which to remove the object
* object: upon return, the object will point to the object which was stored
* in the element of the list just removed. 
*/
int list_remove(struct list *list, const struct list_tuple *tuple, void **object);

/*
* inserts the object into the list
*
* list: the list into which the object will be inserted
* tuple: the tuple after which to insert the object
* if the tuple is a NULL, a new tuple is inserted at head of the list
* object: an object to add to the list. If the tuple is NULL, the object will
* be inserted at the head of the list
*/
int list_insert(struct list *list, struct list_tuple *tuple, const void *object);

int list_destroy(struct list **list);

int list_create(struct list **list, const struct list_attr *attr);

#endif

