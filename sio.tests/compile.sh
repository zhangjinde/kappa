#!/bin/sh

# Compilation script for simple io routines tests
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

[[ -d .output ]] && rm -rv .output || : ; 
install -d -v .output;
pushd .output;

install -v ../../.output/libio.dylib .;

cc -g -O0 -Wall -std=c89 \
    -Wl,-lio,-L. \
    -Wl,-rpath,@executable_path/ \
    -Wl,-rpath,@loader_path/ \
    -Wl,-rpath,@rpath_path/ \
    ../test.file.c \
    -o test;

popd;

