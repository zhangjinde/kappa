/*
* buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef BUFFER_H
#define BUFFER_H

typedef struct buffer buffer_t;

void buffer_destroy(buffer_t *buffer);
int buffer_create(buffer_t **buffer, size_t size); 

#endif

