#include <stdio.h>
#include <string.h>

#include "shell.h"

int execute_command(char** args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    return 1;
}
