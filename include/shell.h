#pragma once

#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

typedef enum {
    INPUT_OK,
    INPUT_EOF,
    INPUT_TOO_LONG
} input_status;

input_status read_input(char* buffer, size_t size);
char* trim(char* str);
char** parse_command(char* command);
bool execute_command(char** args);
