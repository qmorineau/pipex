/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea < qmorinea@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:58:12 by quentin           #+#    #+#             */
/*   Updated: 2024/12/19 19:20:24 by qmorinea         ###   ########.fr       */
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

void	execve_error(t_params *params)
{
	free_params(&params);
	perror("execve failed");
	exit(EXIT_FAILURE);
}
