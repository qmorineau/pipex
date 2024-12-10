#include "pipex.h"

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
	{
		free_tab(&tab);
		return (NULL);
	}
	command->command = tab[0];
	len = 0;
	while(tab[len])
		len++;
	command->args = malloc(sizeof(char *) * len);
	if (!command->args)
	{
		free(command);
		free_tab(&tab);
		return (NULL);
	}
	len = 0;
	while (tab[len + 1])
	{
		command->args[len] = tab[len + 1];
		len++;
	}
	command->args[len] = 0;
	free(tab);
	return (command);
}
