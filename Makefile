# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS = -std=c89 -g -O0
WARN = -Wall -Weverything -Wpedantic

OBJECTS += daemon.o
OBJECTS += sequence.o
TESTS += test_daemon
TESTS += test_sequence

$(TESTS): $(OBJECTS)
	$(CC) $(CFLAGS) $(WARN) $@.c -o $@ $(OBJECTS)

test: $(TESTS)
	@(for test in $(TESTS); do \
        ./$$test; \
    done)

clean:
	rm -rf $(OBJECTS) $(TESTS) *.dSYM

