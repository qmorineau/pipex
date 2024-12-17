#include "pipex.h"

void exec_cmd(char* cmd, char *envp[])
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
		free_tab(&args);
		return ;
	}
	if (execve(path, args, NULL) == -1)
		execve_error();
}