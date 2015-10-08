/*
* file io wrapper utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef FILE_H
#define FILE_H

int file_exists(const char *path);
int file_is_empty(const char *path);
int file_create(const char *path);
int file_remove(const char *path);

#endif

