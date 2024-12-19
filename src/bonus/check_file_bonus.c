/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:37:25 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/19 18:46:31 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_file_in(char *argv)
{
	int	fd;

	fd = access(argv, F_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	fd = access(argv, R_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return ;
	}
	else
	{
		fd = open("/dev/null", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	fd = open(argv, O_RDONLY);
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
	{
		perror("open fail");
		exit(1);
	}
}

int	check_file_out(char *file)
{
	int	fd;

	fd = access(file, F_OK);
	if (fd < 0)
		return (1);
	fd = access(file, W_OK);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
	{
		perror("open fail");
		exit(1);
	}
	return (1);
}
