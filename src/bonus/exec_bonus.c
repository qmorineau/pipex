/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:01:06 by quentin           #+#    #+#             */
/*   Updated: 2025/01/04 16:11:57 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_params *params, char *cmd, char *envp[])
{
	char	**args;
	char	*path;

	args = ft_split(cmd, 32);
	if (!args || !args[0])
	{
		free_tab(&args);
		return ;
	}
	if (!access(cmd, X_OK))
	{
		if (execve(cmd, args, NULL) == -1)
			print_error(params, ERR_EXEC);
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
	free_tab(&args);
	print_error(params, ERR_EXEC);
}
