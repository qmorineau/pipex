/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:00:45 by quentin           #+#    #+#             */
/*   Updated: 2024/12/08 11:54:53 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/pipex.h"

t_cmd *parse_cmd(char *argv)
{
	char	**tab;
	t_cmd	*command;
	int		len;

	tab = ft_split(argv, 32);
	if (!tab)
		return (NULL);
	command = malloc(sizeof(t_cmd));
	if (!command)
	{
		free_tab(&tab);
		return (NULL);
	}
	command->command = tab[0];
	len = 0;
	while(tab[len])
		len++;
	command->args = malloc(sizeof(char *) * len);
	if (!command->args)
	{
		free(command);
		free_tab(&tab);
		return (NULL);
	}
	len = 0;
	while (tab[len + 1])
	{
		command->args[len] = tab[len + 1];
		len++;
	}
	command->args[len] = 0;
	free(tab);
	return (command);
}

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
		wait(&pid);
		close(p[1]);
		pipe_read(p);
	}
	else
	{
		close(p[0]);
		//pipe_write(p);
		close(p[1]);
		if (execve(cmd, args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
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
	int input;
	int ouput;

	if (argc < 5)
		return (printf("error handling, not enough args"), 0);
	else
	{
		input = open(argv[1], O_RDONLY);
		if (input < 0)
			return (printf("error handling, not a file1"), 0);
		ouput = open(argv[argc - 1], O_WRONLY);
		if (ouput < 0)
			return (printf("error handling, not a file2"), 0);
		do_command(argc, argv);
		close(input);
		close(ouput);
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