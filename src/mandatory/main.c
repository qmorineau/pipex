#include "pipex.h"

static int	check_file(char *argv)
{
	int	fd;

	fd = access(argv, F_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (fd);
	}
	fd = access(argv, R_OK);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (fd);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Failed to open\n", 2);
	}
	return (fd);
}

static t_params *create_params(int argc, char *argv[], char *envp[], int fd_in)
{
	t_params *params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->argc = argc;
	params->argv = argv;
	params->envp = envp;
	params->fd_in = fd_in;
	return (params);
}

int main(int argc, char *argv[], char *envp[])
{
	t_params	*params;
	int			fd_in;
	int			fd_out;
	int			exit_status;

	if (argc == 5)
	{
		fd_in = check_file(argv[1]);
		if (fd_in < 0)
		{
			fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd_out > 0)
				close(fd_out);
			return (1);
		}
		params = create_params(argc, argv, envp, fd_in);
		if (!params)
			return (1); /* error func failed malloc */
		exit_status = forking(params);
		free_params(&params);
		return (exit_status);
	}
	else
		return (ft_putstr_fd(strerror(22), 2), 1);
}
