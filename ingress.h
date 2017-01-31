/*
* ingress structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#ifndef INGRESS_H
#define INGRESS_H

int start_ingress(
    const char *host,
    unsigned short port,
    unsigned short queue
);

#endif

