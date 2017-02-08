/*
* log utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include "log.h"

enum {
    log_opt = LOG_CONS | LOG_NDELAY | LOG_NOWAIT | LOG_PID,
    log_fac = LOG_LOCAL0,
    log_mask = LOG_DEBUG
};

enum {
    buffer_size_limit = 0x0100
};

typedef enum {
    error_unknown,
    error_chars_discarded
} error_t;

static const struct {
    const char *message;
    const int number;
    const int flag;
} errors[] = {
    [error_unknown] = { "unknown error", 0x0fa0, 0 },
    [error_chars_discarded] = { "some of the characters were discarded from the logged message", 0x0fa1, 0 }
};

static void make_log_message(
    char *bf,
    size_t bfsz,
    const char *fmt,
    va_list varg, 
    int err_num
) {
    int e;
    const char *err_msg = NULL;

    if (err_num)
        err_msg = strerror(err_num);

    memset(bf, 0, bfsz);

    if ((e = vsnprintf(bf, bfsz, fmt, varg)) < 0)
        syslog(LOG_CRIT, "%m");
    else if ((size_t)e >= bfsz)
        syslog(LOG_WARNING, "%s: [%d]",
            errors[error_chars_discarded].message,
            errors[error_chars_discarded].number
        );

    if (err_msg) {
        if ((e = snprintf(bf, bfsz, "%s, %s: [%d]", bf, err_msg, err_num)) < 0)
            syslog(LOG_CRIT, "%s, %s: [%d]", __func__, strerror(errno), errno);
        else if ((size_t)e >= bfsz)
            syslog(LOG_WARNING, "%s: [%d]",
                errors[error_chars_discarded].message,
                errors[error_chars_discarded].number
            );
    }
}

static void trace(const char *fmt, ...) {
    va_list varg;

    va_start(varg, fmt);
    log_trace(fmt, varg);
    va_end(varg);
}

void log_debug(const char *fmt, va_list varg) {
    const int err_num = errno;
    char bf[buffer_size_limit];

    make_log_message(bf, sizeof(bf), fmt, varg, 0);

    errno = err_num;
}

void log_trace(const char *fmt, va_list varg) {
    const int err_num = errno;
    char bf[buffer_size_limit];

    make_log_message(bf, sizeof(bf), fmt, varg, 0);

    errno = err_num;
}

void log_warning(const char *fmt, va_list varg) {
    const int err_num = errno;
    char bf[buffer_size_limit];

    make_log_message(bf, sizeof(bf), fmt, varg, 0);

    errno = err_num;
}

void log_error(const char *fmt, va_list varg, int err_num) {
    char bf[buffer_size_limit];

    make_log_message(bf, sizeof(bf), fmt, varg, err_num);
}

void log_fatal(const char *fmt, va_list varg, int err_num) {
    char bf[buffer_size_limit];

    make_log_message(bf, sizeof(bf), fmt, varg, err_num);
}

void log_deinit(const char *module) {
    const int err_num = errno;

    closelog();

    trace("deinitialized logging for [%s]", module);
    errno = err_num;
}

void log_init(const char *module) {
    const int err_num = errno;

    openlog(module, log_opt, log_fac);
    setlogmask(LOG_UPTO(log_mask));

    trace("initialized logging for [%s]", module);
    errno = err_num;
}

