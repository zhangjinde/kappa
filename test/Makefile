# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS += -g -O0
CFLAGS += -Wall -Wextra -I../

QUIET_CC = @echo CC $@;

prefixed_objects = $(addprefix ../,$(objects))

tests += test-log
tests += test-fatal
tests += test-error
tests += test-hash
tests += test-file
tests += test-stream
tests += test-buffer
tests += test-stringlib
tests += test-daemon

harnesses += test-fatal-harness
harnesses += test-daemon-harness

test: force tests; @(for test in $(tests); do ./test.sh $$test; done)
tests: $(tests) $(harnesses);
$(tests): %: %.c; $(CC) $(CFLAGS) $(prefixed_objects) -o $@ $<
$(harnesses): %: %.c; $(CC) $(CFLAGS) $(prefixed_objects) -o $@ $<
clean: force;
	@rm -rf \
        $(tests) $(tests:=.o) $(tests:=.dSYM) \
        $(harnesses) $(harnesses:=.o) $(harnesses:=.dSYM)
force:

