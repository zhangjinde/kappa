/* simple io utility structures and routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SIO_ERROR_H
#define SIO_ERROR_H

#include "sio_closure.h"

struct error_type { const int value; const char *format; };
int error_report(int value, ...);
int error_finally(struct closure *finally, int value, ...);

#endif

