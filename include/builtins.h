#pragma once

#include <stddef.h>

typedef int (*builtin_fn)(char **args);

typedef struct {
    const char *name;
    builtin_fn func;
} builtin_t;

extern const builtin_t builtins[];
extern const size_t n_builtins;
