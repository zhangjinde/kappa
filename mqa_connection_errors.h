/*
This file is part of Kappa.
Copyright (C) 2014-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
*/

#ifndef MQA_CONNECTION_ERRORS_H
#define MQA_CONNECTION_ERRORS_H

/*
The AMQP Connection Errors enumeration.
*/
enum connection_errors {
    /*
    An operator intervened to close the connection for some reason. The client
    could retry at some later date.
    */
    connection_forced,

    /*
    A valid frame header cannot be formed from the incoming byte stream.
    */
    framing_error,

    /*
    The container is no longer available on the current connection. The peer
    SHOULD attempt reconnection to the container using the details provided in
    the info map.
    */
    redirect
};

#endif

