/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:01:38 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 08:17:05 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exit_status(pid_t last_pid)
{
	int	status;
	int	exit_status;

	status = 0;
	exit_status = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			if (last_pid != waitpid(last_pid, &status, 0))
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

int	forking(t_params *params)
{
	int		i;
	int		prev_pipe[2];	
	int		current_pipe[2];
	pid_t	pid;
	pid_t	last_pid;

	i = -1;
	while (++i + 2 < params->argc)
	{
		if (pipe(current_pipe))
			pipe_error(params->fd_in);
		pid = fork();
		if (pid == -1)
			fork_error(current_pipe, params);
		else if (pid == 0)
			pipe_child(prev_pipe, current_pipe, params, i);
		else
		{
			parent_pipe(prev_pipe, current_pipe, i, params->argc);
			last_pid = pid;
		}
	}
	return (exit_status(last_pid));
}
