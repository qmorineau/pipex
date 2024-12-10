/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:00:45 by quentin           #+#    #+#             */
/*   Updated: 2024/12/10 18:46:59 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/pipex.h"

void free_command(t_cmd **command)
{
	free((*command)->command);
	free_tab(&(*command)->args);
	free(*command);
	*command = NULL;
}

int create_pipe(int p[2])
{
	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(1);
	}
	return (1);
}

void pipe_read(int p[2])
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
			break;
	}
}

/* void pipe_write(int p[2])
{
	
} */

void exec_cmd(char *cmd, char **args)
{
	pid_t	pid;
	int		p[2];

	create_pipe(p);
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
		//pipe_write(p);l
		
		if (execve(cmd, args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	wait();
}

int do_command(int argc, char *argv[])
{
	int		i;
	t_cmd	*tmp;
	int		len;
	char	*s;
	char	**tab;

	i = 2;
	while (i < argc)
	{
		tmp = parse_cmd(argv[i]);
		if (!tmp)
			return (0);
		len = ft_strlen(tmp->command) + 6;
		s = calloc(sizeof(char), len);
		ft_strlcpy(s, "/bin/", len);
		ft_strlcat(s, tmp->command, len);
		tab = ft_split(argv[i], 32);
		free(tab[0]);
		tab[0] = s;
		exec_cmd(s, tab);
		free_command(&tmp);
		free_tab(&tab);
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	if (argc < 5)
		return (printf("error handling, not enough args"), 0);
	else
	{
		int f1 = access(argv[1], F_OK);
		int f2 = access(argv[argc - 1], F_OK);
		if (f1 < 0 || f2 < 0)
			return(printf("error file exist\n"));
		f1 = access(argv[1], R_OK);
		f2 = access(argv[argc - 1], W_OK);
		if (f1 < 0 || f2 < 0)
			return(printf("error read / write\n"));
		printf("f1 = %d, f2 = %d\n", f1, f2);
		do_command(argc, argv);
	}
}

/* int main(void)
{
	char buffer[4];
	int p[2];
	int i;

	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(1);
	}
	write(p[1], "abc", 3);
	write(p[1], "def", 3);
	write(p[1], "gh", 3);

	i = 0;
	while (i < 3)
	{
		read(p[0], buffer, 3);
		printf("%s\n", buffer);
		i++;
	}
	close(p[0]);
	close(p[1]);
} */

/* 
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
 */