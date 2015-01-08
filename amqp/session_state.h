/* session state
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef SESSION_STATE_H
#define SESSION_STATE_H

/* The AMQP Session State enumeration. */
enum session_state {
    /* In the UNMAPPED state, the session endpoint is not mapped to any incoming
    or outgoing channels on the connection endpoint. In this state an endpoint
    cannot send or receive frames. */
    unmapped,

    /* In the BEGIN SENT state, the session endpoint is assigned an outgoing
    channel number, but there is no entry in the incoming channel map. In this
    state the endpoint MAY send frames but cannot receive them. */
    begin_swnt,

    /* In the BEGIN RCVD state, the session endpoint has an entry in the incoming
    channel map, but has not yet been assigned an outgoing channel number. The
    endpoint MAY receive frames, but cannot send them. */
    begin_received,

    /* In the MAPPED state, the session endpoint has both an outgoing channel
    number and an entry in the incoming channel map. The endpoint MAY both send
    and receive frames. */
    mapped,
};

#endif

