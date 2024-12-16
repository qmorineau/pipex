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

void do_pipe(int pipe[2], int in_out)
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

/* 
			if (i == 0)
				pipe_input_file(fd);
			if (i != 0)
				pipe_not_first(prev_pipe);
			if (i < argc - 4)
				pipe_not_last(current_pipe);
			else
				pipe_output_file(argv[argc - 1]);
			if (i + 2 < argc - 1)
				test_exec(argv[i + 2], envp);
 */