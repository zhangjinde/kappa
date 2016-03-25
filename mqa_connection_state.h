/* connection state 
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#ifndef MQA_CONNECTION_STATE_H
#define MQA_CONNECTION_STATE_H

/* The AMQP Connection State enumeration. */
enum connection_state {
    /* In this state a connection exists, but nothing has been sent or received.
    This is the state an implementation would be in immediately after
    performing a socket connect or socket accept. */
    start,

    /* In this state the connection header has been received from the peer but a
    connection header has not been sent. */
    header_received,

    /* In this state the connection header has been sent to the peer but no
    connection header has been received. */
    header_sent,

    /* In this state the connection header has been sent to the peer and a
    connection header has been received from the peer. */
    header_exchanged,
    
    /* In this state both the connection header and the open frame have been sent
    but nothing has been received. */
    open_pipe,

    /* In this state, the connection header, the open frame, any pipelined
    connection traffic, and the close frame have been sent but nothing has been
    received. */
    open_close_pipe,

    /* In this state the connection headers have been exchanged. An open frame has
    been re- ceived from the peer but an open frame has not been sent. */
    open_received,

    /* In this state the connection headers have been exchanged. An open frame has
    been sent to the peer but no open frame has yet been received. */
    open_sent,

    /* In this state the connection headers have been exchanged. An open frame,
    any pipelined connection traffic, and the close frame have been sent but no
    open frame has yet been received from the peer. */
    close_pipe,

    /* In this state the connection header and the open frame have been both sent
    and received. */
    opened,

    /* In this state a close frame has been received indicating that the peer has
    initiated an AMQP close. No further frames are expected to arrive on the
    connection; however, frames can still be sent. If desired, an
    implementation MAY do a TCP half-close at this point to shut down the read
    side of the connection. */
    close_received,

    /* In this state a close frame has been sent to the peer. It is illegal to
    write anything more onto the connection, however there could potentially
    still be incoming frames. If desired, an implementation MAY do a TCP
    half-close at this point to shutdown the write side of the connection. */
    close_sent,

    /* The DISCARDING state is a variant of the CLOSE SENT state where the close
    is triggered by an error. In this case any incoming frames on the
    connection MUST be silently discarded until the peer's close frame is
    received. */
    discarding,

    /* In this state it is illegal for either endpoint to write anything more onto
    the connection. The connection can be safely closed and discarded. */
    end
};

#endif

