/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:58:31 by quentin           #+#    #+#             */
/*   Updated: 2024/12/20 11:56:50 by qmorinea         ###   ########.fr       */
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
# define ERR_EXEC 0
# define ERR_OPEN 1

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
void	print_error(t_params *params, int err);
/* Pipes */
int		do_pipes(t_params *params);
void	pipe_parent(int pipe_fd[2]);
void	pipe_child(int pipe_fd[2], t_params *params, int i, int is_heredoc);
/* Exec */
void	exec_cmd(t_params *params, char *cmd, char *envp[]);
/* Path */
char	*find_path(char *cmd, char *envp[]);
/* Check */
void	check_file_in(t_params *params, char *argv);
int		check_file_out(t_params *params, char *argv, int is_heredoc);
/* Heredoc */
int		here_doc(t_params *params);
#endif