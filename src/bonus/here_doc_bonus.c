/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/20 12:13:28 by qmorinea         ###   ########.fr       */
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
		close(fd);
		check_file_in(params, ".tmp_pipex");
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
