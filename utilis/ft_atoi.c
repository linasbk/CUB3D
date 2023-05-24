/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/21 15:13:01 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(1, &(*s), 1);
		s++;
	}
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isspace(char str)
{
	if (str == '\t' || str == '\f' || str == '\v'
		|| str == '\n' || str == '\r' || str == ' ')
		return (1);
	return (0);
}

long	ft_atoi(char *str)
{
	long	num;

	num = 0;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (INT_MAX + 1l);
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + *str - 48;
		str++;
	}
	if (*str && !ft_isspace(*str))
		return (INT_MAX + 1l);
	return (num);
}
