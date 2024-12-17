#include "pipex.h"

void pipe_error(int fd)
{
	perror("pipe fail");
	close(fd);
	exit(EXIT_FAILURE);
}

void fork_error(int pipe[2], t_params *params)
{
	close(pipe[0]);
	close(pipe[1]);
	close(params->fd_in);
	free(params);
	exit(1);
}

void execve_error(void)
{
	perror("execve failed");
	exit(EXIT_FAILURE);
}