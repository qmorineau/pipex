#include "pipex.h"

char **create_args_execve(t_cmd *command)
{
	char **args;

	

	return ()
}

void test(int argc, char *argv[], int input, int output)
{
	printf("input = %d\n", input);
	char *args[] = {"/bin/ls", "-l","-a", NULL};
    char *env[] = {NULL};

	(void) argc;
	(void) argv;
    // Replace the current process with /bin/ls
    if (execve("/bin/ls", args, env) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
	printf("output = %d\n", output);
}

t_cmd *parse_cmd(char *argv)
{
	char	**tab;
	t_cmd	*command;
	int		len;

	tab = ft_split(argv, 32);
	if (!tab)
		return (NULL);
	command = malloc(sizeof(t_cmd));
	if (!command)
		return (free_tab(&tab), NULL);
	command->command = tab[0];
	len = 0;
	while(tab[len])
		len++;
	command->flags = malloc(sizeof(char *) * len);
	if (!command->flags)
	{
		free(command);
		free_tab(&tab);
		return (NULL)
	}
	len = 0;
	while (tab[len + 1])
		command->flags[len] = tab[++len];
	command->flags[len] = 0;
	return (command);
}

int main(int argc, char *argv[])
{
	int input;
	int ouput;

	if (argc < 5)
		return (printf("error handling, not enough args"), 0);
	else
	{
		input = open(argv[1], O_RDONLY);
		if (input < 0)
			return (printf("error handling, not a file1"), 0);
		ouput = open(argv[argc - 1], O_WRONLY);
		if (ouput < 0)
			return (printf("error handling, not a file2"), 0);
		test(argc, argv, input, ouput);
		close(input);
		close(ouput);
	}
}

/* 
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
 */