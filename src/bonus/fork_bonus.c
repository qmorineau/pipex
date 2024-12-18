/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:01:38 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 12:17:44 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	check_file_in(char *argv)
{
	int	fd;

	fd = access(argv, F_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	fd = access(argv, R_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return ;
	}
	fd = open(argv, O_RDONLY);
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
	{
		fd = open("/dev/null", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
}

int	forking(t_params *params)
{
	int		i;
	int		pipes[2];
	pid_t	pid;
	pid_t	last_pid;

	i = -1;
	check_file_in(params->argv[2]);
	while (++i + 2 < params->argc)
	{
		if (pipe(pipes))
			pipe_error(params->fd_in);
		pid = fork();
		if (pid == -1)
			fork_error(pipes, params);
		else if (pid == 0)
		{
			close(pipes[0]);
			if (dup2(pipes[1], STDOUT_FILENO) == -1)
				perror("dup2 fail");
			close(pipes[1]);
			exec_cmd(params->argv[i + 2], params->envp);
		}
		else
		{
			close(pipes[1]);
			if (dup2(pipes[0], STDIN_FILENO) == -1)
				perror("dup2 fail");
			close(pipes[0]);
			last_pid = pid;
		}
	}
	int fd;
	if (!check_file_out(params->argv[i + 2]))
		exit(1);
	fd = open(params->argv[i + 2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
	return (exit_status(last_pid));
}