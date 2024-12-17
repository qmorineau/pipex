/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:15:14 by quentin           #+#    #+#             */
/*   Updated: 2024/12/17 14:15:18 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_pipe(int prev_pipe[2], int current_pipe[2], int i, int argc)
{
	if (i > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (i < argc - 4)
	{
		prev_pipe[0] = current_pipe[0];
		prev_pipe[1] = current_pipe[1];
	}
	if (i == argc - 4)
	{
		close(current_pipe[0]);
		close(current_pipe[1]);
	}
}
