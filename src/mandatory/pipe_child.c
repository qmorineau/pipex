#include "pipex.h"

static void pipe_input_file(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

static void pipe_output_file(char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

static void do_pipe(int pipe[2], int in_out)
{
	if (in_out == STDIN_FILENO)
	{
		close(pipe[1]);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			perror("dup2 fail");
		close(pipe[0]);
	}
	else
	{
		close(pipe[0]);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			perror("dup2 fail");
		close(pipe[1]);
	}
}

void pipe_child(int prev_pipe[2], int current_pipe[2], t_params *params, int i)
{
	if (i == 0)
		pipe_input_file(params->fd_in);
	if (i != 0)
		do_pipe(prev_pipe, STDIN_FILENO);
	if (i < params->argc - 4)
		do_pipe(current_pipe, STDOUT_FILENO);
	else
		pipe_output_file(params->argv[params->argc - 1]);
	if (i + 2 < params->argc - 1)
		exec_cmd(params->argv[i + 2], params->envp);
}