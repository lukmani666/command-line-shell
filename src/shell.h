#ifndef SHELL_H
#define SHELL_H
#include <ncurses.h>

void start_shell();
char *read_input();
char **parse_input(char *input);
int execute_command(char **args);

#endif