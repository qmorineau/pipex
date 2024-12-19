/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:03:10 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 07:45:33 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int			i;

	if (argc >= 5)
	{
		params = create_params(argc, argv, envp);
		if (!params)
			return (1);
		i = -1;
		while (++i + 2 < params->argc - 2)
			exit_status = forking(params);
		free_params(&params);
		return (exit_status);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}
