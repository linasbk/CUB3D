/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/14 19:13:08 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
	{
			*(unsigned char *)(b + len) = (unsigned char)c;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(size * count);
	if (!str)
		return (0);
	ft_memset(str, 0, size * count);
	return (str);
}

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

int	ft_strlen(char *s)
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
