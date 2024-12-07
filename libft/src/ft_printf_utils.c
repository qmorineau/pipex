/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmorinea <qmorinea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:46:58 by qmorinea          #+#    #+#             */
/*   Updated: 2024/10/24 14:53:27 by qmorinea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_putchar_fd(char c, int fd, int *count)
{
	int	i;

	i = write(fd, &c, 1);
	if (i < 0 || (*count) == -1)
		(*count) = -1;
	else
		(*count)++;
}

void	printf_putstr_fd(char *s, int fd, int *count)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		printf_putstr_fd("(null)", fd, count);
		return ;
	}
	while (s[i])
	{
		printf_putchar_fd(s[i++], fd, count);
		if (*count == -1)
			return ;
	}
}
