/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:08:52 by qmorinea          #+#    #+#             */
/*   Updated: 2025/01/04 16:04:18 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exit_status(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	status = 0;
	exit_status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

static void	pipe_child(int pipe_fd[2], t_params *params, int i)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(pipe_fd[1]);
	if (i + 2 == params->argc - 2)
	{
		if (!check_file_out(params, params->argv[params->argc - 1]))
		{
			free_params(&params);
			exit(1);
		}
	}
	exec_cmd(params, params->argv[i + 2], params->envp);
	free_params(&params);
	exit(1);
}

static void	pipe_parent(int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2 fail");
	close(pipe_fd[0]);
}

int	do_pipes(t_params *params)
{
	int		i;
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	last_pid;

	i = -1;
	check_file_in(params, params->argv[1]);
	while (++i + 2 < params->argc - 1)
	{
		if (pipe(pipe_fd))
			pipe_error(params->fd_in);
		pid = fork();
		if (pid == -1)
			fork_error(pipe_fd, params);
		else if (pid == 0)
			pipe_child(pipe_fd, params, i);
		else
		{
			pipe_parent(pipe_fd);
			last_pid = pid;
		}
	}
	free_params(&params);
	return (exit_status(last_pid));
}
