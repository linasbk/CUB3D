/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:55:18 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/23 12:52:08 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_retline(t_cub3d_data *cub)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = ft_strlen(cub->line);
	if (!cub->line)
		return (FAILURE);
	line = ft_strtrim(cub->line, "\n");
	free(cub->line);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (FAILURE);
		else
			i++;
	}
	while (j < cub->m_index)
	{
		if (cub->matrice[j][0] == '\0')
			return (FAILURE);
		j++;
	}
	cub->matrice = ft_split(line, '\n');
	return (free(line), SUCCESS);
}

int	ft_error(char *s)
{
	ft_putstr("\033[1;31mError!!\n");
	ft_putstr(s);
	ft_putstr("\n");
	return (FAILURE);
}
