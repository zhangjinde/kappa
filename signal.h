/*
* signal library of utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef SIGNALLIB_H
#define SIGNALLIB_H

#include <signal.h>

const char *signal_signame(int sig); 
void signal_trace_sigset(const sigset_t *sigset, const char *s); 
void signal_trace_sigaction(int sig, const siginfo_t *siginfo);
void signal_trace_sigprocmask(); 
void signal_trace_sigpending(); 

#endif

