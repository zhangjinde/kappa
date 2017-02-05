/*
* fatal utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef FATAL_H
#define FATAL_H

#include <stdarg.h>
#include <stdnoreturn.h>

_Noreturn void fatal(const char *fmt, ...);

#endif

