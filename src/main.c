#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 1024

char* trim(char* str) {
    while (isspace(*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end > str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int main(void) {
    char input[INPUT_SIZE];

    while (1) {
        printf("myshell> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        char* command = trim(input);

        printf("%s\n", command);

        if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    return 0;
}
