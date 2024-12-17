/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:58:31 by quentin           #+#    #+#             */
/*   Updated: 2024/12/17 14:23:11 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_params
{
	int		argc;
	char	**argv;
	char	**envp;
	int		fd_in;
}		t_params;
/* Free */
void	free_tab(char ***tab);
void	free_params(t_params **params);
/* Errors */
void	pipe_error(int fd);
void	fork_error(int pipe[2], t_params *params);
void	execve_error(void);
/* Pipes */
void	parent_pipe(int prev_pipe[2], int current_pipe[2], int i, int argc);
void	pipe_child(int prev_pipe[2], int current_pipe[2],
			t_params *params, int i);
/* Fork */
int		forking(t_params *params);
/* Exec */
void	exec_cmd(char *cmd, char *envp[]);
/* Path */
char	*find_path(char *cmd, char *envp[]);
#endif