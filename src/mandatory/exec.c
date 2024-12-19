/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:01:06 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 19:21:47 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_params *params, char *cmd, char *envp[])
{
	char	**args;
	char	*path;

	args = ft_split(cmd, 32);
	if (!args)
		return ;
	if (!access(cmd, X_OK))
	{
		if (execve(cmd, args, NULL) == -1)
			execve_error(params);
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		free_tab(&args);
		free_params(&params);
		exit(127);
	}
	execve(path, args, NULL);
	free(path);
	path = NULL;
	free_tab(&args);
	execve_error(params);
}
