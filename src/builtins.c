#include "builtins.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

char *builtin_str[] = {
    "cd",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &cd,
    &shell_exit
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    // if (strcmp(args[0], "cd") == 0) {
    //     return cd(args);
    // } else if (strcmp(args[0], "exit") == 0) {
    //     return shell_exit(args);
    // } else if (strcmp(args[0], "pwd") == 0) {
    //     return pwd(args);
    // } else if (strcmp(args[0], "history") == 0) {
    //     return shell_history(args);
    // }

    // if (has_pipe(args)) {
    //     return handle_pipe(args);
    // }

    // if (has_redirection(args)) {
    //     return handle_redirection(args);
    // }

    // if (args[0][strlen(args[0]) - 1] == '&') {
    //     args[0][strlen(args[0]) - 1] = '\0';
    //     return handle_background(args);
    // }

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch_program(args);
}

int launch_program(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int shell_exit(char **args) {
    return 0;
}

// int pwd(char **args) {
//     char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         printf("%s\n", cwd);
//     } else {
//         perror("shell");
//     }

//     return 1;
// }

// #define MAX_HISTORY 50
// char *history[MAX_HISTORY];
// int history_count = 0;

// void add_to_history(char *input) {
//     if (history_count < MAX_HISTORY) {
//         history[history_count++] = strdup(input);
//     } else {
//         free(history[0]);
//         for (int i = 1; i < MAX_HISTORY; i++) {
//             history[i - 1] = history[i];
//         }
//         history[MAX_HISTORY - 1] = strdup(input);
//     }
// }

// int shell_history(char **args) {
//     for (int i = 0; i < history_count; i++) {
//         printf("%d %s\n", i + 1, history[i]);
//     }
//     return 1;
// }


// int has_pipe(char **args) {
//     for (int i = 0; args[i] != NULL; i++) {
//         if (strcmp(args[i], "|") == 0) {
//             return 1;
//         }
//     }

//     return 0;
// }

// int has_redirection(char **args) {
//     for (int i = 0; args[i] != NULL; i++) {
//         if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<")) {
//             return 1;
//         }
//     }

//     return 0;
// }

// int handle_pipe(char **args) {
//     int pipe_fd[2];
//     pid_t pid1, pid2;

//     if (pipe(pipe_fd) == -1) {
//         perror("pipe");
//         return 1;
//     }

//     pid1 = fork();
//     if (pid1 == 0) {
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[0]);
//         execvp(args[0], args);
//         perror("execvp");
//         exit(1);
//     } else if (pid1 < 0) {
//         perror("fork");
//         return 1;
//     }

//     pid2 = fork();
//     if (pid2 == 0) {
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[1]);
//         execvp(args[2], &args[2]);
//         perror("execvp");
//         exit(1);
//     } else if (pid2 < 0) {
//         perror("fork");
//         return 1;
//     }

//     close(pipe_fd[0]);
//     close(pipe_fd[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
//     return 1;
// }

// int handle_redirection(char **args) {
//     int fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1) {
//         perror("open");
//         return 1;
//     }

//     dup2(fd, STDOUT_FILENO);
//     close(fd);

//     execvp(args[0], args);
//     perror("execvp");
//     exit(1);
// }

// int handle_background(char **args) {
//     pid_t pid = fork();

//     if (pid == 0) {
//         execvp(args[0], args);
//         perror("execvp");
//         exit(1);
//     } else if (pid > 0) {
//         return 1;
//     } else {
//         perror("fork");
//         return 1;
//     }
// }

