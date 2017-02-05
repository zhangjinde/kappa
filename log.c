/*
* log utility structures and routines
* Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
* This file is part of Kappa.
*/

#include <syslog.h>
#include "log.h"

void log_fatal(const char *msg) {
    syslog(LOG_EMERG, "%s", msg);
}

void log_error(const char *msg) {
    syslog(LOG_ERR, "%s", msg);
}

void log_warning(const char *msg) {
    syslog(LOG_WARNING, "%s", msg);
}

void log_trace(const char *msg) {
    syslog(LOG_INFO, "%s", msg);
}

void log_debug(const char *msg) {
    syslog(LOG_DEBUG, "%s", msg);
}

void log_init(const char *module) {
    openlog(module,
        LOG_CONS | LOG_NDELAY | LOG_NOWAIT | LOG_PID, LOG_LOCAL0
    );
}

