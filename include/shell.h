#pragma once

#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

bool read_input(char* buffer, size_t size);
char* trim(char* str);
char** parse_command(char* command);
void execute_command(char** args);
