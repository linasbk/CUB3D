/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:25:38 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/19 21:50:08 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_comma(t_cub3d_data *cube, char *line)
{
	int comma;
	int i;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return(ft_error("Invalid color"));
	else if (comma == 2 &&line[i - 2] == ',')
		return(ft_error("Invalid color"));
	return (SUCCESS);
}

int	check_range(t_cub3d_data *cube, char *line)
{
	t_map_color	*color;
	char		**str;
	int			i;

	i = 0;
	str = ft_split(line, ',');
	color->r = ft_atoi(str[0]);
	color->g = ft_atoi(str[1]);
	color->b = ft_atoi(str[2]);
	if (color->r < 0 || color->r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return(ft_error("Invalid color"));
	return (SUCCESS);
}

