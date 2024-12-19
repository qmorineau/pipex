/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:02:30 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 09:34:54 by qmorinea         ###   ########.fr       */
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
	free(*params);
	*params = NULL;
}
