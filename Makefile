# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS = -g -O0
CFLAGS += -Wall -Wextra
CFLAGS += -iquote.. -fmodule-map-file=module.modulemap

QUIET_CC = @echo CC $@;

objects += log.o
objects += fatal.o
objects += error.o
objects += warning.o
objects += trace.o
objects += debug.o
objects += string.o
objects += signal.o
objects += hash.o
objects += file.o
objects += stream.o
objects += buffer.o
objects += inet-stream.o
objects += daemon.o

export objects

objects: $(objects)
$(objects): %.o: %.c %.h; $(QUIET_CC)$(CC) $(CFLAGS) -o $@ -c $<
test: force $(objects)
	@$(MAKE) -s -C test;
clean: force
	@rm -rf $(objects);
	@$(MAKE) -s -C test clean;
force:

