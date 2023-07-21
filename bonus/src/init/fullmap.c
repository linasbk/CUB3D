/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 09:28:39 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/21 14:33:41 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	puts_player(t_cub3d_data *cub)
{
	int	x;
	int	y;

	x = cub->player->mpx - 5;
	y = cub->player->mpy - 4;
	while (++y < cub->player->mpy + 5)
	{
		x = cub->player->mpx - 5;
		while (x < cub->player->mpx + 5)
		{
			if (distance(cub->player->mpx, \
			cub->player->mpy, x, y) < 5)
				mlx_put_pixel(cub->map_img, x, y, BLACK_MP);
			x++;
		}
	}
}

void	background_fullmap(t_cub3d_data *cub)
{
	int	x;
	int	y;

	x = 200;
	y = 199;
	while (++y < HEIGHT_FULLMAP + 195)
	{
		x = 200;
		while (x < WIDTH_FULLMAP + 195)
			mlx_put_pixel(cub->map_img, x++, y, get_color(255, 255, 255, 50));
	}
}

void	framing_norm(t_cub3d_data *cub)
{
	int			x;
	int			y;

	y = HEIGHT_FULLMAP + 194;
	while (++y < HEIGHT_FULLMAP + 200)
	{
		x = 195;
		while (x < WIDTH_FULLMAP + 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	y = 194;
	while (++y < HEIGHT_FULLMAP + 200)
	{
		x = WIDTH_FULLMAP + 195;
		while (x < WIDTH_FULLMAP + 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
}

void	framing_fullmap(t_cub3d_data *cub)
{
	int			x;
	int			y;

	y = 194;
	while (++y < 200)
	{
		x = 195;
		while (x < WIDTH_FULLMAP + 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	y = 194;
	while (++y < HEIGHT_FULLMAP + 200)
	{
		x = 195;
		while (x < 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	framing_norm(cub);
}

void	setting_map(t_cub3d_data *cub)
{
	framing_fullmap(cub);
	background_fullmap(cub);
	cub->y_wall = HEIGHT_FULLMAP / cub->len_j;
	cub->x_wall = cub->y_wall;
	cub->beginx = (WIDTH / 2) - ((cub->len_i * cub->x_wall) / 2);
	cub->beginy = (HEIGHT / 2) - ((cub->len_j * cub->y_wall) / 2);
	draw_fullmap(cub);
	cub->player->mpx = ((cub->player->x / WALL_DIMENSION) \
	* cub->x_wall) + cub->beginx;
	cub->player->mpy = ((cub->player->y / WALL_DIMENSION) \
	* cub->y_wall) + cub->beginy;
	puts_player(cub);
}
