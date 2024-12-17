/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:02:30 by quentin           #+#    #+#             */
/*   Updated: 2024/12/17 14:03:00 by quentin          ###   ########.fr       */
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
