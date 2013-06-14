/* set structure and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

/* TODO: complete the set interface */

#ifndef SET_H
#define SET_H

struct set {};

void set_init(struct set *set, void (* destroy)(void *));
void set_destroy(struct set *set);

#endif

