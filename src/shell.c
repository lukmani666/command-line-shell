#include "shell.h"
#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void start_shell() {
    char *input;
    char **args;
    int status = 1;
    char cwd[1024];

    do {
        // printf("> ");
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s>", cwd);
        } else {
            perror("getcwd() error");
            return;
        }
        input = read_input();
        
        // add_to_history(input);
        args = parse_input(input);

        status = execute_command(args);

        free(input);
        free(args);
    } while (status);
}
