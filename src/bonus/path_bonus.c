/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:14:41 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 08:17:11 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*try_path(char *cmd, char **tab, int i)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(tab[i], "/");
	path = ft_strjoin(tmp, cmd);
	free_str(&tmp);
	if (!access(path, X_OK))
	{
		free_tab(&tab);
		return (path);
	}
	free_str(&path);
	return (NULL);
}

static char	*parse_path(char *cmd, char *env_line)
{
	char	**tab;
	int		i;
	char	*path;

	if (!access(cmd, X_OK))
		return (cmd);
	tab = ft_split(env_line + 5, ':');
	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		if (!access(tab[i], X_OK))
			path = try_path(cmd, tab, i);
		if (path)
			return (path);
	}
	free_tab(&tab);
	perror("command not found");
	return (NULL);
}

char	*find_path(char *cmd, char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = parse_path(cmd, envp[i]);
			if (path)
				return (path);
		}
		i++;
	}
	return (NULL);
}
