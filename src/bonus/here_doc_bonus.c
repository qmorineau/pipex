/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/20 11:21:25 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	pipe_child(int pipe_fd[2], t_params *params, int i, int is_heredoc)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(pipe_fd[1]);
	if (i + 3 == params->argc - 2)
	{
		if (!check_file_out(params, params->argv[params->argc - 1], is_heredoc))
		{
			free_params(&params);
			exit(1);
		}
	}
	exec_cmd(params, params->argv[i + 3], params->envp);
	exit(1);
}

static void	pipe_parent(int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2 fail");
	close(pipe_fd[0]);
}

static void	read_stdin(t_params *params)
{
	char	*line;
	char	*eof;
	int		fd;

	eof = ft_strjoin(params->argv[2], "\n");
	if (!eof)
		return ;
	fd = open(".tmp_pipex", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd >= 0)
	{
		line = get_next_line(0);
		while (line && ft_strncmp(eof, line, ft_strlen(eof)))
		{
			write(fd, line, ft_strlen(line));
			free_str(&line);
			line = get_next_line(0);
		}
		write(fd, line, ft_strlen(line));
		close(fd);
		fd = open(".tmp_pipex", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		unlink(".tmp_pipex");
		free_str(&line);
	}
	free_str(&eof);
}

int	here_doc(t_params *params)
{
	int		i;
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	last_pid;

	i = -1;
	read_stdin(params);
	while (++i + 3 < params->argc - 1)
	{
		if (pipe(pipe_fd))
			pipe_error(params->fd_in);
		pid = fork();
		if (pid == -1)
			fork_error(pipe_fd, params);
		else if (pid == 0)
			pipe_child(pipe_fd, params, i, 1);
		else
		{
			pipe_parent(pipe_fd);
			last_pid = pid;
		}
	}
	free_params(&params);
	return (exit_status(last_pid));
}
