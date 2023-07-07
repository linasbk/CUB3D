/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:25:38 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/07 15:26:59 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_comma(t_cub3d_data *cube, char *line)
{
	int	comma;
	int	i;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (ft_error("Invalid color"));
	else if (comma == 2 && line[i - 2] == ',')
		return (ft_error("Invalid color"));
	return (SUCCESS);
}

t_map_color	*check_range(t_cub3d_data *cube, char *line)
{
	t_map_color	*color;
	char		**str;
	int			i;

	i = 0;
	color = malloc(sizeof(t_map_color));
	color->r = 0;
	color->g = 0;
	color->b = 0;
	str = NULL;
	str = ft_split(line, ',');
	color->b = ft_atoi(str[0]);
	color->g = ft_atoi(str[1]);
	color->r = ft_atoi(str[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		ft_error("Invalid coloor");
		exit(FAILURE);
	}
	return (color);
}

t_map_color	*valide_color(t_cub3d_data *cub, char *str)
{
	t_map_color	*color;

	if (check_comma(cub, str) == FAILURE)
		exit(FAILURE);
	color = check_range(cub, str);
	return (color);
}
