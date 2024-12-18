/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:03:10 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 13:27:05 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static int	check_file_in(char *argv)
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
} */

int	check_file_out(char *argv)
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

static t_params	*create_params(int argc, char *argv[], char *envp[])
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->argc = argc;
	params->argv = argv;
	params->envp = envp;
	return (params);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_params	*params;
	int			exit_status;

	if (argc == 5)
	{
		params = create_params(argc, argv, envp);
		if (!params)
			return (1);
		exit_status = forking(params);
		free_params(&params);
		return (exit_status);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}
