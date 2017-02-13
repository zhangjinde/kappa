# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS += -g -O0
CFLAGS += -Wall -Wextra -I../

QUIET_CC = @echo CC $@;

objects += log.o
objects += fatal.o
objects += error.o
objects += warning.o
objects += trace.o
objects += debug.o
objects += stringlib.o
objects += signallib.o
objects += hash.o
objects += stream.o
objects += daemon.o

tests += test-log
tests += test-fatal
tests += test-error
tests += test-hash
tests += test-stream
tests += test-stringlib
tests += test-daemon

harnesses += test-fatal-harness
harnesses += test-daemon-harness

objects: $(objects)
$(objects): %.o: ../%.c ../%.h; $(QUIET_CC)$(CC) $(CFLAGS) -o $@ -c $<
test: force tests; @(for test in $(tests); do ./test.sh $$test; done)
tests: $(objects) $(tests) $(harnesses);
$(tests): %: %.c $(objects); $(QUIET_CC)$(CC) $(CFLAGS) $(objects) -o $@ $<
$(harnesses): %: %.c; $(QUIET_CC)$(CC) $(CFLAGS) $(objects) -o $@ $<
clean: force;
	@rm -rf \
        $(objects) \
        $(tests) $(tests:=.o) $(tests:=.dSYM) \
        $(harnesses) $(harnesses:=.o) $(harnesses:=.dSYM)
force:

