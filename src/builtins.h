#ifndef BUILTINS_H
#define BUILTINS_H

int cd(char **args);
int shell_exit(char **args);
int execute_command(char **args);
int launch_program(char **args);
// int pwd(char **args);
// int shell_history(char **args);
// void add_to_history(char *input);
// int handle_pipe(char **args);
// int handle_redirection(char **args);
// int handle_background(char **args);
// int has_pipe(char **args);
// int has_redirection(char **args);

#endif