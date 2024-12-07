#include "pipex.h"

void test(int argc, char *argv[], int input, int output)
{
	printf("input = %d\n", input);
	char *args[] = {"/bin/ls", "-l", "-a", NULL};
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

char **parse_cmd(char *argv)
{
	char **tab;

	tab = ft_split(argv, 32);
	if (!tab)
		return (NULL);
	
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