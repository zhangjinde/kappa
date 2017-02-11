/*
* string extension utility routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <string.h>
#include <math.h>
#include "string-extension.h"

void string_reverse(char *s) {
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void string_from_int(char *s, int n) {
    /* cast to an unsigned to handle a case of INT_MIN */
    unsigned u;
    int i, is_neg;

    u = (is_neg = n < 0) ? -n : n;
    
    for (i = 0; (!i && !u) || (u); i++, u /= 10)
        s[i] = (u % 10) + '0';
    if (is_neg) s[i] = '-';
    s[++i] = '\0';
    string_reverse(s);
}

