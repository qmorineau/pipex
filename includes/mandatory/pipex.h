/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:58:31 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 07:42:25 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
/* Fork */
int		forking(t_params *params);
/* Exec */
void	exec_cmd(char *cmd, char *envp[]);
/* Path */
char	*find_path(char *cmd, char *envp[]);
/* Check */
void	check_file_in(char *argv);
int		check_file_out(char *argv);
#endif