/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:23 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/12 20:58:52 by qmorinea         ###   ########.fr       */
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

/* static int create_pipe(int p[2])
{
    if (pipe(p) < 0)
    {
        perror("pipe");
        exit(1);
    }
    return (1);
} */

/* static void pipe_read(int p[2])
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
} */

/* static void pipe_write(int p[2])
{
	int	i;

    i = 0;
    while (p[1])
    {
        
    }
} */

/* static void forking(int argc, char *argv[], char *env[])
{
    int     p[2];
    pid_t   pid;
    char    **tab;
    int fd;
	int i;

	i = 1;
    (void) env;
    fd = open(argv[1], O_RDONLY);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
    if (fd < 0)
        return ;
    while (++i < argc - 1)
    {
        create_pipe(p);
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            close(p[0]);
			dup2(p[1], STDOUT_FILENO);
            pipe_read(p);
        }
        else
        {
            close(p[1]);
			dup2(p[0], STDIN_FILENO);
			close(p[0]);P
            //pipe_write(p);
            tab = ft_split(argv[i], 32);
            int len = ft_strlen(tab[0]) + 6;
            char *s = (char *) ft_calloc(sizeof(char), len);
            ft_strlcpy(s, "/bin/", len);
		    ft_strlcat(s, tab[0], len);
            if (execve(s, tab, NULL) == -1)
            {
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
        }
    }
    wait(NULL);
} */

int	**create_pipe(int argc)
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
		i++;
	}
	return (p);
}

void read_pipe(int **p, int cmd_idx, int last_cmd_idx)
{
	if (cmd_idx > 2)
	{
		dup2(p[cmd_idx][0], STDIN_FILENO);
		/* link file */
	}
	else if (cmd_idx <  last_cmd_idx)
	{
		dup2(p[cmd_idx - 1][1], STDOUT_FILENO);
		/* link last pipe */
	}
	/* close pipe */

	/* do execution of cmd */
}

void test_exec(char* cmd)
{
	char **tab = ft_split(cmd, 32);
	int len = ft_strlen(tab[0]) + 6;
	char *s = (char *) ft_calloc(sizeof(char), len);
	ft_strlcpy(s, "/bin/", len);
	ft_strlcat(s, tab[0], len);
	printf("%s\n", s);
	if (execve(s, tab, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
void write_pipe(int **p, int cmd_idx)
{
	int fd;

	close(p[cmd_idx - 1][0]);
	fd = p[cmd_idx][1];
	wait(NULL);
	char *s = get_next_line(fd);
	while (s)
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		free(s);
		s = get_next_line(fd);
	}
	close(p[cmd_idx][1]);
	fd = p[cmd_idx][0];
	s =  get_next_line(fd);
	while (s)
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		free(s);
		s = get_next_line(fd);
	}
}


static void forking(int argc, char *argv[], char *env[])
{
	int fd;
	int i;
	int **p;
	pid_t pid;

	(void) env;
	fd = open(argv[1], O_RDONLY);
	/* protect open */
	p = create_pipe(argc);
	dup2(fd, p[0][1]);
	if (!p)
		return ;
	/* better protect */
	i = 1;
	while (++i < argc - 3)
	{
		pid = fork();
		/* protect pid */
		dup2(p[i][0], STDIN_FILENO);
		dup2(p[i][1], STDOUT_FILENO);
		if (pid == 0) /* child */
		{
			read_pipe(p, i, argc - 3);
			test_exec(argv[i]);
		}
		else
		{
			write_pipe(p, i);
		}
	}
	wait(NULL);
	int file = access(argv[argc - 1], F_OK);
	if (file < 0)
	{
		file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else
		file = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	char *s = get_next_line(STDIN_FILENO);
	while (s)
	{
		ft_putstr_fd(s, file);
		free(s);
		s = get_next_line(STDIN_FILENO);
	}
	close(file);
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