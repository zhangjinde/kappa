/*
* log utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef LOG_H
#define LOG_H

void log_fatal(const char *msg);
void log_error(const char *msg);
void log_warning(const char *msg);
void log_trace(const char *msg);
void log_debug(const char *msg);
void log_init(const char *module);

#endif

