#include <stdio.h>

#include "shell.h"

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("myshell> ");

        if (!read_input(buffer, BUFFER_SIZE)) {
            break;
        }

        char** args = parse_command(trim(buffer));

        if (args == NULL) {
            continue;
        }

        execute_command(args);
    }

    return 0;
}
