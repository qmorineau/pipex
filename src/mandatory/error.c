/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:58:12 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 19:39:00 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_error(int fd)
{
	perror("pipe fail");
	close(fd);
	exit(EXIT_FAILURE);
}

void	fork_error(int pipe[2], t_params *params)
{
	close(pipe[0]);
	close(pipe[1]);
	free(params);
	exit(1);
}

void	print_error(t_params *params, int err)
{
	free_params(&params);
	if (err == ERR_EXEC)
		perror("execve failed");
	else if (err == ERR_OPEN)
		perror("open failed");
	exit(EXIT_FAILURE);
}
