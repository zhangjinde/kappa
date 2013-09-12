/* test driver
Copyright (C) 2013-2017 Roman Fakhrazeyev <roman.fakhrazeyev@xinoir.com>
This file is part of Kappa. */

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "test.h"
#include "fixture.h"

int main(int argc, char[] *argv) {
    void *handle;
    void (*test_exec)();
    handle = dlopen("xxx.so", RTLD_NOW);
    if(!handle) {
        fprintf(stderr, "error %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    *(void **)(&test_exec) = dlsym(handle, "test_exec");
    char *error;
    if((error = dlerror()) != NULL) {
        fprintf(stderr, "error %s\n", error);
        exit(EXIT_FAILURE);
    }
    (*test_exec)();
    dlclose(handle);
    exit(EXIT_SUCCESS);
}

