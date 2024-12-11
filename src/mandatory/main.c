/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/11 20:01:33 by qmorinea         ###   ########.fr       */
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

static int	create_pipe(int p[2])
{
	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(1);
	}
	return (1);
}

static void	pipe_read(int p[2])
{
	int		byte_read;
	char	*buff[100];

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(p[0], buff, 100);
		if (byte_read < 0)
			return ;
		if (byte_read == 0)
			break ;
	}
}

static void	pipe_write(int p[2])
{
	int	i;

	i = 0;
	while (p[1])
	{
	}
}

static void	forking(int argc, char *argv[], char *env[])
{
	int		i;
	int		p[2];
	pid_t	pid;
	char	**tab;
	int		fd;
	int		len;
	char	*s;

	i = 1;
	(void)env;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return ;
	while (++i < argc - 1)
	{
		printf("i = %d\n", i);
		create_pipe(p);
		p[0] = dup2(fd, p[0]);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			close(p[1]);
			pipe_read(p);
		}
		else
		{
			close(p[0]);
			pipe_write(p);
			tab = ft_split(argv[i], 32);
			len = ft_strlen(tab[0]) + 6;
			s = (char *)ft_calloc(sizeof(char), len);
			ft_strlcpy(s, "/bin/", len);
			ft_strlcat(s, tab[0], len);
			if (execve(s, tab, NULL) == -1)
			{
				perror("execve failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	wait(&pid);
}

int	main(int argc, char *argv[], char *env[])
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
