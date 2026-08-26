#include "executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins.h"

int run_external(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(args[0], args);
        fprintf(stderr, "myshell: command not found: %s\n", args[0]);
        _exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int run_embedded(const unsigned char *data, size_t size, char *const argv[]) {
    int fd = memfd_create(argv[0], MFD_CLOEXEC);

    if (fd < 0) {
        perror("memfd_create");
        return 1;
    }

    ssize_t written = write(fd, data, size);

    if (written < 0 || (size_t)written != size) {
        perror("write");
        close(fd);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        fexecve(fd, argv, environ);
        perror("myshell:");
        _exit(EXIT_FAILURE);
    }

    close(fd);

    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n_builtins; i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);
        }
    }

    run_external(args);

    return 0;
}
