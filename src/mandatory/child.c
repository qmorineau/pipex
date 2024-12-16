#include "pipex.h"

void pipe_input_file(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

void pipe_output_file(char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(fd);
}

void pipe_not_last(int current_pipe[2])
{
	close(current_pipe[0]);
	if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
		perror("dup2 fail");
	close(current_pipe[1]);
}

void pipe_not_first(int prev_pipe[2])
{
	close(prev_pipe[1]);
	if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
		perror("dup2 fail ici");
	close(prev_pipe[0]);
}