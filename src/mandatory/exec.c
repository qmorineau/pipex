#include "pipex.h"

void execve_error(void)
{
	perror("execve failed");
	exit(EXIT_FAILURE);
}
void test_exec(char* cmd, char *envp[])
{
	char **args;
	char *path;

	args = ft_split(cmd, 32);
	//free_tab(&args);
	if (!args)
		return ;
	if (!access(cmd, X_OK))
	{
		if (execve(cmd, args, NULL) == -1)
			execve_error();
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		if (execve(args[0], args, NULL) == -1)
			execve_error();
	}
	if (execve(path, args, NULL) == -1)
		execve_error();
}

