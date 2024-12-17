#include "pipex.h"

void    free_tab(char ***tab)
{
    int i;

    if (tab && *tab)
    {
        i = 0;
        while (tab[0][i])
        {
            free(tab[0][i]);
            tab[0][i] = NULL;
            i++;
        }
        free(*tab);
        *tab = NULL;
    }
}

void	free_params(t_params **params)
{
	close((*params)->fd_in);
	free(*params);
	*params = NULL;
}
