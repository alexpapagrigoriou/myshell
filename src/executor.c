#include "executor.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins.h"

static int setup_input_redirect(char **args) {
    int redirect = -1;

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            redirect = i;
            break;
        }
    }

    if (redirect < 0) {
        return 0;
    }

    if (redirect == 0) {
        fprintf(stderr, "myshell: missing command before '<'\n");
    }

    if (args[redirect + 1] == NULL) {
        fprintf(stderr, "myshell: missing input file\n");
    }

    char *input_file = args[redirect + 1];

    int fd = open(input_file, O_RDONLY);

    if (fd < 0) {
        perror("open");
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return -1;
    }

    close(fd);

    args[redirect] = NULL;

    return 1;
}

static int setup_output_redirect(char **args) {
    int redirect = -1;

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            redirect = i;
            break;
        }
    }

    if (redirect < 0) {
        return 0;
    }

    if (redirect == 0) {
        fprintf(stderr, "myshell: missing command before '>'\n");
        return -1;
    }

    if (args[redirect + 1] == NULL) {
        fprintf(stderr, "myshell: missing output file\n");
        return -1;
    }

    char *output_file = args[redirect + 1];

    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return -1;
    }

    close(fd);

    args[redirect] = NULL;

    return 1;
}

int run_external(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        if (setup_output_redirect(args) < 0) {
            _exit(EXIT_FAILURE);
        }

        if (setup_input_redirect(args) < 0) {
            _exit(EXIT_FAILURE);
        }

        execvp(args[0], args);
        perror("myshell");
        _exit(EXIT_FAILURE);
    }

    int status;

    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }

    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int run_embedded(const unsigned char *data, size_t size, char **argv) {
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

    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }

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
