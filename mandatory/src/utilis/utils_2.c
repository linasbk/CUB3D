/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:16:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/15 13:09:50 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_space(char str)
{
	if (str == '\t' || str == ' ')
		return (1);
	return (0);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (n > i)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*new_ptr;
	size_t	size;

	if (ptr == 0)
		return (ft_calloc(1, newsize));
	size = sizeof(ptr);
	if (newsize <= size)
		return (ptr);
	new_ptr = ft_calloc(1, newsize);
	ft_memcpy(ptr, new_ptr, size);
	free(ptr);
	return (new_ptr);
}

int	resizematrice(t_cub3d_data *cub, int num_lines)
{
	int	i;
	int	currentlength;
	int	diff;

	i = 0;
	while (i < num_lines)
	{
		currentlength = ft_strlen(cub->matrice[i]);
		diff = cub->len_i - currentlength;
		if (diff > 0)
		{
			cub->matrice[i] = ft_realloc(cub->matrice[i], (currentlength + \
					diff + 1) * sizeof(char));
			ft_memset(cub->matrice[i] + currentlength, ' ', diff);
			cub->matrice[i][currentlength + diff] = '\0';
		}
		i++;
	}
	return (num_lines);
}
