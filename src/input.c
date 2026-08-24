#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "shell.h"

input_status read_input(char* buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return INPUT_EOF;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && feof(stdin)) {
        return INPUT_EOF;
    }

    if (len == size - 1 && buffer[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (c == EOF) {
            return INPUT_EOF;
        }

        return INPUT_TOO_LONG;
    }

    return INPUT_OK;
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
