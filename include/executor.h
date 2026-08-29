#pragma once

#include <stddef.h>

int run_external(char **args);
int run_embedded(const unsigned char *data, size_t size, char **argv);
int execute_command(char **args);
