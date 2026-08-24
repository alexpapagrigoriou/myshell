#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "shell.h"

bool read_input(char* buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }

    return true;
}

char* trim(char* str) {
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}
