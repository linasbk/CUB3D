/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/10 22:25:29 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_square(mlx_image_t *img, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == size - 1 || i == size - 1 || j == 0 || i == 0)
				mlx_put_pixel(img, x + i, y + j, BLACK_MP);
			else
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	cast_allrays(int color, t_cub3d_data *cub)
{
	float	colmnID = 0;
	int		i = 0;
	float	num_rays;

	num_rays = cub->len_i * WALL_DIMENSION;
	cub->data_rays->ray_angle = cub->player_data->rot_angle - (FOV_ANGLE/ 2);
	while (i < num_rays)
	{
		ray_cast(cub, colmnID);
		cub->data_rays->ray_angle += FOV_ANGLE / num_rays;
		i++;
		colmnID++;
	}
}

int	distance(int i, int j, int x, int y)
{
	return (sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

void	put_player(t_cub3d_data *cub)
{
	int	x2;
	int	y2;

	x2 = 0;
	y2 = 0;
	while (y2 < cub->len_j * WALL_DIMENSION)
	{
		x2 = 0;
		while (x2 < cub->len_i * WALL_DIMENSION)
		{
			if (distance(x2, y2, cub->player_data->x, cub->player_data->y) \
				<= P_RADIUS)
				mlx_put_pixel(cub->map_img, x2, y2, ORANGE_MP);
			x2++;
		}
		y2++;
	}
	cast_allrays(RED_MP, cub);
}

void	mini_map_framing(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->len_i * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, i++, j, RED_MP);
	i = 0;
	while (i < cub->len_i * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, i++, cub->len_j * WALL_DIMENSION - 1, RED_MP);
	j = 0;
	while (j < cub->len_j * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, cub->len_i * WALL_DIMENSION, j++, RED_MP);
	j = 0;
	while (j < cub->len_j * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, cub->len_i * WALL_DIMENSION - 1, j++, RED_MP);
}

void	put_map(t_cub3d_data *cub)
{
	int	i;
	int	j;

	j = 0;
	cub->map_img = mlx_new_image(cub->mlx, cub->len_i * WALL_DIMENSION, cub->len_j * WALL_DIMENSION);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	while (cub->matrice[j])
	{
		i = 0;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == '1')
				draw_square(cub->map_img, i * WALL_DIMENSION, j * WALL_DIMENSION, WALL_DIMENSION, WHITE_MP  );
			i++;
		}
		j++;
	}
	put_player(cub);
	mini_map_framing(cub);
}
