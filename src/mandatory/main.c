/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/16 15:48:01 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_file(char *argv)
{
	int	file;

	file = access(argv, F_OK);
	if (file < 0)
		return (perror(""), 0);
	file = access(argv, R_OK);
	if (file < 0)
		return (perror(""), 0);
	return (1);
}



void parent_pipe(int prev_pipe[2], int current_pipe[2], int i, int argc)
{
	if (i > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (i < argc - 4)
	{
		prev_pipe[0] = current_pipe[0];
		prev_pipe[1] = current_pipe[1];
	}
	if (i == argc - 4)
	{
		close(current_pipe[0]);
		close(current_pipe[1]);
	}
}

int forking(int argc, char *argv[], char *envp[])
{
	int i;
	pid_t pid;
	pid_t last_pid;
	int prev_pipe[2];
	int current_pipe[2];

	int fd = open(argv[1], O_RDONLY);
	// protect open
	i = -1;
	while (++i + 2 < argc)
	{
		if (pipe(current_pipe))
			perror("pipe fail");
		pid = fork();
		if (pid == -1)
		{
			close(current_pipe[0]);
			close(current_pipe[1]);
			exit(1);
		}
		else if (pid == 0)
		{
			if (i == 0)
				pipe_input_file(fd);
			if (i != 0)
				do_pipe(prev_pipe, STDIN_FILENO);
			if (i < argc - 4)
				do_pipe(current_pipe, STDOUT_FILENO);
			else
				pipe_output_file(argv[argc - 1]);
			if (i + 2 < argc - 1)
				test_exec(argv[i + 2], envp);
		}
		else
		{
			parent_pipe(prev_pipe, current_pipe, i, argc);
			last_pid = pid;
		}
	}
	int status = 0;
	int exit_status = EXIT_FAILURE;
	
// Wait for all child processes
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			if (last_pid == waitpid(last_pid, &status, 0))
				exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			if (last_pid == waitpid(last_pid, &status, 0))
				exit_status = 128 + WTERMSIG(status);
		}
	}
	return(exit_status); // General failure
}

int main(int argc, char *argv[], char *envp[])
{
	int exit_status;
	int fd;

	if (argc == 5)
	{
		if (!check_file(argv[1]))
		{
			fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			close(fd);
			return (0);
		}
		exit_status = forking(argc, argv, envp);
		(void) exit_status;
		return (0);
    }
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}


/* 
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
 */