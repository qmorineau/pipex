/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:03:10 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 14:29:53 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		exit_status = do_pipes(params);
		free_params(&params);
		return (exit_status);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}
