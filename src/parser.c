#include <stdlib.h>
#include <string.h>

#include "shell.h"

char **parse_command(char *command) {
    char **words = malloc(sizeof(char *) * (BUFFER_SIZE / 2));

    if (words == NULL) {
        return NULL;
    }

    words[0] = strtok(command, " ");

    int i = 0;
    while (words[i] != NULL) {
        i++;
        words[i] = strtok(NULL, " ");
    }

    return words;
}
