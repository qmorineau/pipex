/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:15:23 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 08:03:47 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipe_input_file(int fd)
{
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
	}
	else
	{
		fd = open("/dev/null", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
}

static void	pipe_output_file(char *file)
{
	int	fd;

	if (!check_file_out(file))
		exit(1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

static void	do_pipe(int pipe[2], int in_out)
{
	if (in_out == STDIN_FILENO)
	{
		close(pipe[1]);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(pipe[0]);
	}
	else
	{
		close(pipe[0]);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			perror("dup2 fail");
		close(pipe[1]);
	}
}

void	pipe_child(int prev_pipe[2], int current_pipe[2],
				t_params *params, int i)
{
	if (i == 0)
		pipe_input_file(params->fd_in);
	if (i != 0)
		do_pipe(prev_pipe, STDIN_FILENO);
	if (i < params->argc - 4)
		do_pipe(current_pipe, STDOUT_FILENO);
	else
		pipe_output_file(params->argv[params->argc - 1]);
	if (i + 2 < params->argc - 1)
		exec_cmd(params->argv[i + 2], params->envp);
}
