/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/13 13:34:25 by quentin          ###   ########.fr       */
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

/* int	**create_pipe(int argc)
{
	int	**p;
	int	pipe_nbr;
	int	i;
	int	*tmp;

	pipe_nbr = argc - 3;
	p = (int **) malloc(sizeof(int *) * pipe_nbr);
	if (!p)
		return (NULL);
	i = 0;
	while (i < pipe_nbr)
	{
		tmp = (int *) malloc(sizeof(int) * 2);
		if (!tmp)
			return (NULL);
		p[i] = tmp;
		if (pipe(p[i]) == -1)
		{
			exit(0);
			// error gestion
		}
		i++;
	}
	return (p);
} */

/* void read_pipe(int *pipe)
{
	close(pipe[1]);
    dup2(pipe[0], STDIN_FILENO);
    close(pipe[0]);
} */

/* void write_pipe(int *pipe)
{
	close(pipe[0]);
    dup2(pipe[1], STDOUT_FILENO);
    close(pipe[1]);
} */


// static void forking(int argc, char *argv[], char *env[])
// {
// 	int fd;
// 	int i;
// 	int **p;
// 	pid_t pid;

// 	(void) env;
// 	fd = open(argv[1], O_RDONLY);
// 	/* protect open */
// 	p = create_pipe(argc);
// 	dup2(fd, p[0][1]);
// 	if (!p)
// 		return ;
// 	/* better protect */
// 	i = 1;
// 	while (++i < argc - 3)
// 	{
// 		pid = fork();
// 		/* protect pid */
// 		if (pid == 0) /* child */
// 		{
// 			//printf("child pipe\n");
// 			read_pipe(p[i - 2]);
// 			//printf("before exec\n");
// 			test_exec(argv[i]);
// 		}
// 		else
// 		{
// 			//printf("parent pipe\n");
// 			write_pipe(p[i - 2]);
// 		}
// 	}
// 	wait(NULL);
// 	int file = access(argv[argc - 1], F_OK);
// 	if (file < 0)
// 	{
// 		file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
// 	}
// 	else
// 		file = open(argv[argc - 1], O_WRONLY | O_TRUNC);
// 	char *s = get_next_line(STDIN_FILENO);
// 	while (s)
// 	{
// 		ft_putstr_fd(s, file);
// 		free(s);
// 		s = get_next_line(STDIN_FILENO);
// 	}
// 	close(file);
// }

void test_exec(char* cmd)
{
	char **tab = ft_split(cmd, 32);
	int len = ft_strlen(tab[0]) + 6;
	char *s = (char *) ft_calloc(sizeof(char), len);
	ft_strlcpy(s, "/bin/", len);
	ft_strlcat(s, tab[0], len);
	perror(s);
	if (execve(s, tab, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void forking(int argc, char *argv[], char *env[])
{
	int i;
	pid_t pid;
	int prev_pipe[2];
	int current_pipe[2];

	(void) env;
	int fd = open(argv[1], O_RDONLY);
	// protect open
	i = -1;
	while (++i + 2 < argc)
	{
		pipe(current_pipe);
		// protect pipe
		pid = fork();
		if (pid == -1)
		{
			// protect
			exit(1);
		}
		else if (pid == 0) // child
		{
			if (i == 0)
			{
				dup2(fd, STDIN_FILENO);
				//printf("Redirecting input from file: %s\n", argv[i + 2]);
				close(fd);
			}
			if (i != 0)
			{
				close(prev_pipe[1]);
				dup2(prev_pipe[0], STDIN_FILENO);
				//printf("reading prev pipe: %s\n", argv[i + 2]);
				close(prev_pipe[0]);
			}
			if (i + 2 < argc - 1)
			{
				close(current_pipe[0]);
				//printf("reading current pipe: %s\n", argv[i + 2]);
				dup2(current_pipe[1], STDOUT_FILENO);
				close(current_pipe[1]);
			}
			else
			{
				int file = access(argv[argc - 1], F_OK);
				if (file < 0)
				{
					file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
				}
				else
				{
					file = open(argv[argc - 1], O_WRONLY | O_TRUNC);
				}
				dup2(file, STDOUT_FILENO);
				fflush(stdout);
				//printf("Redirecting output to file: %s\n", argv[argc - 1]);
				close(file);
			}
			if (i + 2 < argc - 1)
				test_exec(argv[i + 2]);
		}
		else // parent
		{
			if (i > 0)
			{
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (i + 2 < argc - 1)
			{
				prev_pipe[0] = current_pipe[0];
				prev_pipe[1] = current_pipe[1];
			}
			if (i + 2 == argc - 1)
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