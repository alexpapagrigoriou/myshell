#include "builtins.h"

#include <stdio.h>
#include <unistd.h>

#include "executor.h"

#define INCBIN_PREFIX asset_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include "../third_party/incbin/incbin.h"

INCBIN(bin_vip, "assets/bin/vip");

static int builtin_cd(char** args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: no argument given\n");
        return 1;
    }

    if (args[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

static int builtin_exit(char** args) {
    (void)args;
    return -1;
}

static int builtin_vip(char** args) {
    run_embedded(asset_bin_vip_data, (size_t)asset_bin_vip_size, args);
    return 0;
}

const builtin_t builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"vip", builtin_vip}};

const size_t n_builtins = sizeof(builtins) / sizeof(builtins[0]);
