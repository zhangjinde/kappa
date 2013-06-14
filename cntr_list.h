/* list structure and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef LIST_H
#define LIST_H

/* attributes for the list creation */
struct list_attr {
    void (* destroy)(void *object);
};

/* an element of the list */
struct  list_tuple {
    void *object;
    struct list_tuple *next;
};

struct list {
    int length;
    struct list_tuple *head;
    struct list_tuple *tail;
    void (*destroy)(void *object);
};

/* Returns the element immediately following the specified element. */
struct list_tuple *list_next(const struct list *list, const struct list_tuple *tuple);

/* Returns the object stored in the element of the list. */
void *list_object(const struct list *list, const struct list_tuple *tuple);

/* Determines whether the element is at the tail of the list. 
Returns 1 if the element is at the tail of the list, 0 otherwise. */
int list_is_tail(const struct list *list, const struct list_tuple *tuple);

/* Determines whether the element is at the head of the list. 
Returns 1 if the element is at the head of the list, 0 otherwise. */
int list_is_head(const struct list *list, const struct list_tuple *tuple);

/* The element at the tail of the list. 
On success, returns the tail element of the list; on error, it returns a NULL. */
struct list_tuple *list_tail(const struct list *list);

/* The element at the head of the list. 
On success, returns the head element of the list; on error, it returns a NULL. */
struct list_tuple *list_head(const struct list *list);

/* The number of the elements in the list. 
On success, returns the length of the list; on error, it returns an error number. */
int list_length(const struct list *list);

/* Removes the element from the list.
list: the list from which the object will remove.
tuple: the tuple after which to remove the object.
object: Upon return, the object will point to the object which was stored
in the element of the list just removed. 
On success, returns 0; on error, it returns an error number. */
int list_remove(struct list *list, const struct list_tuple *tuple, void **object);

/* Inserts the object into the list.
list: the list into which the object will be inserted.
tuple: the tuple after which to insert the object.
object: an object to add to the list. If the tuple is NULL, the object will
be inserted at the head of the list.
On success, returns 0; on error, it returns an error number. */
int list_insert(struct list *list, struct list_tuple *tuple, const void *object);

/* Destroys the list. 
On success, returns 0; on error, it returns an error number. */
int list_destroy(struct list **list);

/* Creates a new list. 
On success, returns 0; on error, it returns an error number. */
int list_create(struct list **list, const struct list_attr *attr);

#endif

