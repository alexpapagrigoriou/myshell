#include <stdio.h>

#include "shell.h"

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("myshell> ");

        input_status status = read_input(buffer, BUFFER_SIZE);

        if (status == INPUT_EOF) {
            printf("\nmyshell> exit\n");
            break;
        }

        if (status == INPUT_TOO_LONG) {
            fprintf(stderr, "myshell: input too long\n");
            continue;
        }

        char** args = parse_command(trim(buffer));

        if (args == NULL) {
            continue;
        }

        if (!execute_command(args)) {
            break;
        }
    }

    return 0;
}
