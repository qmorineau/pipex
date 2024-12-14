/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/14 01:02:29 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_file(char *argv)
{
	int	file;

	file = access(argv, F_OK);
	if (file < 0)
		return (perror("zsh"), 0);
	file = access(argv, R_OK);
	if (file < 0)
		return (perror("zsh"), 0);
	return (1);
}

char *parse_path(char *cmd, char *env_line)
{
	char **tab;
	int	i;
	char	*path;
	char	*tmp;

	if (!access(cmd, F_OK))
		return (cmd);
	tab = ft_split(env_line + 5, ':');
	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		if (!access(tab[i], F_OK))
		{
			tmp = ft_strjoin(tab[i], "/");
			path = ft_strjoin(tmp, cmd);
			free_str(&tmp);
			if (!access(path, F_OK))
			{
				free_str(&cmd);
				free_tab(&tab);
				return(path);
			}
			free_str(&path);
		}
	}
	free_tab(&tab);
	perror("cmd not found");
	return(NULL);
}

char *find_path(char *cmd, char *envp[])
{
	int i;
	char *path;

	i = 0;
	while (envp[i])
	{
		if(ft_strnstr(envp[i], "PATH=", 5))
		{
			path = parse_path(cmd, envp[i]);
			if (path)
				return (path);
		}
		i++;
		strerror(i);
	}
	return (NULL);
}

void test_exec(char* cmd, char *envp[])
{
	char **args;
	char *path;

	args = ft_split(cmd, 32);
	if (!args)
		perror("split not work");
	path = find_path(args[0], envp);
	if (!path)
		perror("no path");
	if (execve(path, args, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void pipe_input_file(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

void pipe_output_file(char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

void pipe_not_last(int current_pipe[2])
{
	close(current_pipe[0]);
	if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(current_pipe[1]);
}

void pipe_not_first(int prev_pipe[2])
{
	close(prev_pipe[1]);
	if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
		perror("dup2 fail ici");
	close(prev_pipe[0]);
}

void forking(int argc, char *argv[], char *envp[])
{
	int i;
	pid_t pid;
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
			{
				//perror("test\n");
				pipe_not_first(prev_pipe);
			}
			if (i < argc - 4)
				pipe_not_last(current_pipe);
			else
				pipe_output_file(argv[argc - 1]);
			if (i + 2 < argc - 1)
				test_exec(argv[i + 2], envp);
		}
		else
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
	}
	for (i = 0; i + 2 < argc; i++) {
        wait(NULL);
    }
}

int main(int argc, char *argv[], char *env[])
{
	(void)env;
	if (argc == 5)
	{
		if (!check_file(argv[1]))
			return (1);
		forking(argc, argv, env);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
	return (0);
}


/* 
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
 */