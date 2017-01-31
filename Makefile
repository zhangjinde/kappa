# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS += -std=c89 -g -O0
CFLAGS += -Wall -Weverything -Wpedantic
CFLAGS += -Wno-declaration-after-statement -Wno-c99-extensions
CFLAGS += -Wno-reserved-id-macro -Wno-pointer-arith

QUIET_CC = @echo CC $@;

objects += stream.o
objects += daemon.o
objects += sequence.o
objects += hash.o

tests += test-stream
tests += test-daemon
tests += test-sequence
tests += test-hash

objects: $(objects)
$(objects): %.o: %.c %.h; $(QUIET_CC)$(CC) $(CFLAGS) -o $@ -c $<
test: force tests; @(for test in $(tests); do ./test.sh $$test; done)
tests: $(objects) $(tests);
$(tests): %: %.c; $(QUIET_CC)$(CC) $(CFLAGS) $(objects) -o $@ $<
clean: force; @rm -rf $(objects) $(tests) $(tests:=.o) $(tests:=.dSYM)
force:

