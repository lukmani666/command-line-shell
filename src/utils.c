#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


char *read_input() {
    char *input = NULL;
    size_t bufsize = 0;
    __ssize_t line_size = getline(&input, &bufsize, stdin);
    if (line_size == -1) {
        perror("getline");
        exit(1);
    }
    return input;

}

char **parse_input(char *input) {
    int bufsize = 64, position = 0;
    char **args = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(input, " \t\r\n\a");
    while (token != NULL) {
        args[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            args = realloc(args, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \t\r\n\a");

    }
    args[position] = NULL;
    return args;
}