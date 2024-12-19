/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:37:25 by qmorinea          #+#    #+#             */
/*   Updated: 2024/12/19 20:14:59 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	no_read_perm(t_params *params, char *argv)
{
	int	fd;

	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	fd = open("/dev/null", O_RDONLY);
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
		print_error(params, ERR_OPEN);
}

static void	create_output_file(t_params *params, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
		print_error(params, ERR_OPEN);
}

void	check_file_in(t_params *params, char *argv)
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
		no_read_perm(params, argv);
		return ;
	}
	fd = open(argv, O_RDONLY);
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(fd);
	}
	else
		print_error(params, ERR_OPEN);
}

int	check_file_out(t_params *params, char *file)
{
	int	fd;

	fd = access(file, F_OK);
	if (fd < 0)
	{
		create_output_file(params, file);
		return (1);
	}
	fd = access(file, W_OK);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		create_output_file(params, file);
		return (1);
	}
	return (0);
}
