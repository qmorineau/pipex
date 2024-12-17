#include "pipex.h"

void parent_pipe(int prev_pipe[2], int current_pipe[2], int i, int argc)
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