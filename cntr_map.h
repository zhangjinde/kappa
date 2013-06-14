/* map structure and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

/* TODO: complete the map interface */

#ifndef MAP_H
#define MAP_H

/* attributes for the map creation */
struct map_attr {
    void (* destroy)(void *);
};

struct map {
    void (* destroy)(void *);
};

int map_destroy(struct map **);
int map_create(struct map **, const struct map_attr *);

#endif

