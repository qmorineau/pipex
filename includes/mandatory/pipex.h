#ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../../libft/includes/libft.h"
typedef struct s_cmd
{
    char *command;
    char **args;
}   t_cmd;
/* Free */
void    free_tab(char ***tab);
void	free_string(char **s);
/* Children */
void	pipe_input_file(int fd);
void	pipe_output_file(char *file);
void do_pipe(int pipe[2], int in_out);
/* Exec */
void test_exec(char* cmd, char *envp[]);
/* Path */
char *find_path(char *cmd, char *envp[]);
#endif