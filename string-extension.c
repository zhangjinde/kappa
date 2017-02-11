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
    int i, is_neg;

    if ((is_neg = n < 0)) n = -n;
    for (i = 0; (!i && !n) || (n); i++, n /= 10)
        s[i] = (n % 10) + '0';
    if (is_neg) s[i] = '-';
    s[i++] = '\0';
    string_reverse(s);
}

