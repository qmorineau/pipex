/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:02:30 by quentin           #+#    #+#             */
/*   Updated: 2024/12/18 08:17:07 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char ***tab)
{
	int	i;

	if (tab && *tab)
	{
		i = 0;
		while (tab[0][i])
		{
			free(tab[0][i]);
			tab[0][i] = NULL;
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_params(t_params **params)
{
	close((*params)->fd_in);
	free(*params);
	*params = NULL;
}
