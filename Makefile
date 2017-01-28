# Makefile for Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

CC = cc
CFLAGS += -std=c89 -g -O0
CFLAGS += -Wall -Weverything -Wpedantic

objects += stream.o
objects += daemon.o
objects += sequence.o

tests += test-stream
tests += test-daemon
tests += test-sequence

all: $(objects)
test: $(tests); @(for test in $(tests); do ./$$test; done)
test-%: $(objects) test-%.o; $(CC) $(CFLAGS) $^ -o $@
clean: ; rm -f $(objects) $(tests) $(tests:=.o)

