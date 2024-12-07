#include "pipex.h"

void test(int argc, char *argv[], int input, int output)
{
	printf("input = %s\n", argv[1]);
	char *args[] = {"/bin/ls", argv[2], NULL};
    char *env[] = {NULL};

    // Replace the current process with /bin/ls
    if (execve("/bin/cat", args, env) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
	printf("output = %s\n", argv[argc - 1]);
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