/*
* debug signal utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef DEBUG_SIGNAL_H
#define DEBUG_SIGNAL_H

#include <signal.h>
#include <stdarg.h>

const char *debug_signame(int sig); 
void debug_sigset(const sigset_t *sigset); 

#endif

