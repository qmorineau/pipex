/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:03:10 by quentin           #+#    #+#             */
/*   Updated: 2024/12/17 14:23:30 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_file_in(char *argv)
{
	int	fd;

	fd = access(argv, F_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (fd);
	}
	fd = access(argv, R_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (fd);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Failed to open\n", 2);
	}
	return (fd);
}

static int	check_file_out(char *argv)
{
	int	fd;

	fd = access(argv, F_OK);
	if (fd < 0)
		return (1);
	fd = access(argv, W_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	return (1);
}

static t_params	*create_params(int argc, char *argv[], char *envp[], int fd_in)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->argc = argc;
	params->argv = argv;
	params->envp = envp;
	params->fd_in = fd_in;
	return (params);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_params	*params;
	int			fd_in;
	int			exit_status;

	if (argc == 5)
	{
		fd_in = check_file_in(argv[1]);
		if (!check_file_out(argv[argc -1]))
			return (1);
		params = create_params(argc, argv, envp, fd_in);
		if (!params)
			return (1);
		exit_status = forking(params);
		free_params(&params);
		return (exit_status);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}
