#include "shell.h"
#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>

void start_shell() {
    char *input;
    char **args;
    int status = 1;

    do {
        printf("> ");
        input = read_input();
        
        // add_to_history(input);
        args = parse_input(input);

        status = execute_command(args);

        free(input);
        free(args);
    } while (status);
}
