#!/bin/sh

# Compilation script for simple io routines
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

[[ -d .output ]] && rm -rv .output || : ; 
install -d -v .output;
pushd .output;

cc -g -O0 -Wall -std=c89 \
    -Wl,-dylib \
    -Wl,-install_name,@rpath/libio.dylib \
    -Wl,-rpath,@executable_path/ \
    -Wl,-rpath,@loader_path/ \
    ../error.c \
    ../buffer.c \
    -o ./libio.dylib;

popd;

