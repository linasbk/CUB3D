/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullmaputils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 09:34:44 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/24 14:57:13 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	puts_walls(int x, int y, t_cub3d_data *cub, int flag)
{
	int	tmpx;
	int	tmpy;

	tmpx = x;
	tmpy = y;
	while (y < tmpy + cub->y_wall - 1)
	{
		x = tmpx;
		while (x < tmpx + cub->x_wall - 1)
		{
			if (flag == 1)
				mlx_put_pixel(cub->full_map, x++, y, WHITE_MP);
			else if (flag == 2)
				mlx_put_pixel(cub->full_map, x++, y, 0xA9A9A9FF);
			else
				mlx_put_pixel(cub->full_map, x++, y, PURPLE_MP);
		}
		y++;
	}
}

void	draw_fullmap(t_cub3d_data *cub)
{
	int			x;
	int			y;
	int			i;
	int			j;

	i = 0;
	j = -1;
	y = cub->beginy;
	while (cub->matrice[++j])
	{
		i = 0;
		x = cub->beginx;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == '1')
				puts_walls(x, y, cub, 1);
			else if (cub->matrice[j][i] == 'D')
				puts_walls(x, y, cub, 2);
			else if (cub->matrice[j][i] == 'Y')
				puts_walls(x, y, cub, 0);
			i++;
			x += cub->x_wall;
		}
		y += cub->y_wall;
	}
}
