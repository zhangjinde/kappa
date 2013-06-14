/* queue structure and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

/* TODO: complete the queue interface */

#ifndef QUEUE_H
#define QUEUE_H

struct queue {};

void queue_init(struct queue *queue, void (* destroy)(void *));
void queue_destroy(struct queue *queue);

/* Enqueues the object at the tail of the queue.
queue: the queue onto which the object will be enqueued.
object: an object to enqueue.
On success, returns 0; on error, it returns an error number. */
int queue_enqueue(struct queue *queue, const void *object);

/* Dequeues an object from the head of the queue.
queue: the queue from which to dequeue an object.
object: upon return, it points to the dequeued object.
On success, returns 0; on error, it returns an error number. */
int queue_dequeue(struct queue *queue, const void *object);

/* Returns an object stored at the head of the queue, or a NULL if a queue is empty.
queue: the queue from which to return an object.
object: upon return, it points to the dequeued object.
On success, returns an object, or a NULL, if the queue is empty. */
void *queue_peek(const struct queue *queue);

/* Determines a number of objects in the queue.
queue: the queue which size to determine.
object: upon return, it points to the dequeued object.
On success, returns a size of the queue. */
int queue_size(const struct queue *queue);

#endif

