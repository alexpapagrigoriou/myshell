#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

bool execute_command(char** args) {
    if (args[0] == NULL) {
        free(args);
        return true;
    }

    if (strcmp(args[0], "exit") == 0) {
        free(args);
        return false;
    }

    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    free(args);

    return true;
}
