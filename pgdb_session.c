/* postgres session routines
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <assert.h>
#include "libpq-fe.h"

static const char *CONNECTION_INFO_FORMAT = "dbname=%s user=%s";
static const char *CONNECTION_FAILURE = "Unable to connect to the db.\n";
static const char *SQL_INSERT = "INSERT INTO %s(value) VALUES('%s');";

static void error(void *connection) {
    assert(connection);
    err((args){.message = PQerrorMessage((PGconn *)connection)});
    PQfinish(connection);
    abort();
}

static void connection_open(PGconn **connection, char const *db, char const *user) {
    assert(connection && db && user);
    char *connection_info = format(CONNECTION_INFO_FORMAT, db, user);
    *connection = PQconnectdb(connection_info);
    free(connection_info);
    ensure(connection, .func = fail, .message = CONNECTION_FAILURE);
    ensure(PQstatus(*connection) == CONNECTION_OK, .func = error, .arg = *connection, .message = CONNECTION_FAILURE);
    assert(connection);
}

tuple *tuple_write(tuple *tuple) {
    ensure(tuple, .func = null);
    PGconn *connection;
    connection_open(&connection, "gersh", "gersh");
    ensure(connection, .func = fail, .message = CONNECTION_FAILURE);
    char *sql = format(SQL_INSERT, "thought", (*tuple->fields)->value);
    PGresult *result = PQexec(connection, sql);
    free(sql);
    ensure(result && PQresultStatus(result) == PGRES_COMMAND_OK, .func = error, .arg = connection);
    PQclear(result);
    PQfinish(connection);
    return tuple;
}

