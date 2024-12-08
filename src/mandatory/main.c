/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:00:45 by quentin           #+#    #+#             */
/*   Updated: 2024/12/08 01:00:00 by quentin          ###   ########.fr       */
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

void exec_cmd(char *cmd, char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
        exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		return ;
	else
	{
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

/* 
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
 */