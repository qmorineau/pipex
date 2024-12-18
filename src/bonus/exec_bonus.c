/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:01:06 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 08:18:54 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char *cmd, char *envp[])
{
	char	**args;
	char	*path;

	args = ft_split(cmd, 32);
	if (!args)
		return ;
	if (!access(cmd, X_OK))
	{
		if (execve(cmd, args, NULL) == -1)
			execve_error();
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		free_tab(&args);
		exit(127);
	}
	if (execve(path, args, NULL) == -1)
		execve_error();
}
