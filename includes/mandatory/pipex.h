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
#endif