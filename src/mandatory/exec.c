#include "pipex.h"


void test_exec(char* cmd, char *envp[])
{
	char **args;
	char *path;

	args = ft_split(cmd, 32);
	if (!args)
		perror("split not work");
	if (!access(cmd, X_OK))
	{
		if (execve(cmd, args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	if (execve(path, args, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}