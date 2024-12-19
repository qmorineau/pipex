/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:08:52 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/19 18:33:25 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static int	exit_status(pid_t last_pid)
{
	pid_t pid;
	int	status;
	int	exit_status;
	
	return (0);
	status = 0;
	exit_status = 0;
	while (1)
    {
        pid = waitpid(-1, &status, 0);
        if (pid == -1) // No more child processes
            break;
        if (pid == last_pid)
        {
            // Retrieve the exit status of the last process
            if (WIFEXITED(status))
            {
                int last_exit_status = WEXITSTATUS(status);
                printf("Exit status of the last command: %d\n", last_exit_status);
            }
        }
    }
	return (exit_status);
} */

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

static void	pipe_child(int pipe_fd[2], t_params *params, int i)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(pipe_fd[1]);
	if (i + 2 == params->argc - 2)
	{
		if (!check_file_out(params->argv[params->argc - 1]))
			exit(1);
	}
	exec_cmd(params->argv[i + 2], params->envp);
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
	check_file_in(params->argv[1]);
	ft_putstr_fd("begin pipes\n", 2);
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
	return (exit_status(last_pid));
}
