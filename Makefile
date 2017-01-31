# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS += -std=c89 -g -O0
CFLAGS += -Wall -Weverything -Wpedantic
CFLAGS += -Wno-declaration-after-statement -Wno-reserved-id-macro
CFLAGS += -Wno-c99-extensions

QUIET_CC = @echo CC $@;

objects += hash.o
objects += stream.o
objects += daemon.o
objects += sequence.o
objects += ingress.o

tests += test-hash
tests += test-stream
tests += test-daemon
tests += test-sequence
tests += test-ingress

objects: $(objects)
$(objects): %.o: %.c %.h; $(QUIET_CC)$(CC) $(CFLAGS) -o $@ -c $<
test: force tests; @(for test in $(tests); do ./test.sh $$test; done)
tests: $(objects) $(tests);
$(tests): %: %.c; $(QUIET_CC)$(CC) $(CFLAGS) $(objects) -o $@ $<
clean: force; @rm -rf $(objects) $(tests) $(tests:=.o) $(tests:=.dSYM)
force:

