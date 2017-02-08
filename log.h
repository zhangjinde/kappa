/*
* log utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

void log_debug(const char *fmt, va_list varg);
void log_trace(const char *fmt, va_list varg);
void log_warning(const char *fmt, va_list varg);
void log_error(const char *fmt, va_list varg, int err_num);
void log_fatal(const char *fmt, va_list varg, int err_num);
void log_deinit(const char *module);
void log_init(const char *module);

#endif

