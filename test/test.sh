#!/bin/sh

# test utility script for Makefile in Kappa
# Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
# This file is part of Kappa.

$(./$@);
printf "%s %s\n" $@ $([ "$?" -eq "0" ] && echo "PASS" || echo "FAIL");

