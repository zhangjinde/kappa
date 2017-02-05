/*
* buffer structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "buffer.h"

static const short BUFFER_CHUNK = 0x4000;
static const char LONG_STRING_MAX_SIZE = 16;

static void error_concat(char **target, char const *source) {
    if(*target) {
        char buffer[strlen(*target) + 1];
        strcpy(buffer, *target);
        free(*target);
        *target = malloc(strlen(buffer) + strlen(source) + 1);
        strcpy(*target, buffer);
        strcat(*target, source);
    } else {
        *target = malloc(strlen(source) + 1);
        strcpy(*target, source);
    }
}

enum buffer_meta {
    buffer_meta_delimiter = '%',
    buffer_meta_string = 's',
    buffer_meta_integer = 'd',
    buffer_meta_any = 'a'
};

/* writes a string into a buffer */
static void string(struct buffer *buffer, size_t *value_size, const char *string) {
    *value_size = strlen(string);
    memcpy(buffer->cursor, string, *value_size);
}

/* writes an integer into a buffer */
static void integer(struct buffer *buffer, size_t *value_size, int integer) {
    unsigned char string[LONG_STRING_MAX_SIZE];
    sprintf((void*)string, "%d", integer);
    *value_size = strlen((const char*)string);
    memcpy(buffer->cursor, string, *value_size);
}

struct buffer* buffer_new() {
    struct buffer* buffer = (struct buffer*)malloc(sizeof(struct buffer));
    buffer->head = buffer->cursor = malloc(sizeof(unsigned char) * BUFFER_CHUNK);
    return buffer;
}

void buffer_write(struct buffer* buffer, const unsigned char* message, ...) {
    va_list args;
    va_start(args, message);
    for(const unsigned char* item = message; *item; item++) {
        size_t size = strlen((const char*)item);
        unsigned char* delimiter = memchr(item, '%', size);
        enum buffer_meta meta = !delimiter ? buffer_meta_any : ++delimiter; 
        if(!delimiter) {
            memcpy(buffer->cursor, item, size);
            break;
        }
        if(delimiter - item) {
            memcpy(buffer->cursor, item, (delimiter - item));
            buffer->cursor += delimiter-item;
        }
        item = ++delimiter;
        size_t value_size = 0;
        switch(*item) { 
        case buffer_meta_any :
            memcpy(buffer->cursor, item, size);
            break;
        case buffer_meta_string :
            string(buffer, &value_size, va_arg(args, char*));
            break;
        case buffer_meta_integer :
            integer(buffer, &value_size, va_arg(args, int));
            break;
        }
        buffer->cursor += value_size;
    }
    va_end(args);
}

int buffer_size(const struct buffer* buffer) {
    return buffer->cursor - buffer->head;
}

void buffer_reset(struct buffer* buffer) {
    memset(buffer->head, 0, BUFFER_CHUNK); 
    buffer->cursor = buffer->head;
}

void buffer_free(struct buffer* buffer) {
    free(buffer->head);
    free(buffer);
}

/*
* string buffer utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "error.h"
#include "module.h"
#include "sbuffer.h"

int sbuffer_set(char *bf, size_t nb, const char *fmt, ...) {
    va_list argv;
    va_start(argv, format);
    if ((vsnprintf(bf, nb, fmt, argv)) >= nb) {
        va_end(argv);
        return error(bytes_discarded);
    }
    va_end(argv);
    return 0;
}

int sbuffer_copy(char *bf, size_t nb, const char *src) {
    (void)memset(bf, '\0', nb);
    strncpy(bf, src, nb - 1);
    return 0;
}

