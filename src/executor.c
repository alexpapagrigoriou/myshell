#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

void execute_command(char** args) {
    if (args[0] == NULL) {
        free(args);
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        free(args);
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    free(args);
}
