/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/14 21:08:20 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_square(mlx_image_t *img, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (j == size || i == size || j == 0 || i == 0)
				mlx_put_pixel(img, x + i, y + j, BLACK_MP);
			else
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_put_minimap(t_cub3d_data *cub)
{
	int	i;
	int	j;
	int	bx;
	// int	px;
	int	by;
	// int	py;
	int	tmpx;

	i = 0;
	j = 0;
	// px = (cub->player_data->x - (WALL_DIMENSION / 2)) / WALL_DIMENSION;
	// py = (cub->player_data->y - (WALL_DIMENSION / 2)) / WALL_DIMENSION;
	bx = (cub->player_data->x) - 75;
	tmpx = bx;
	by = (cub->player_data->y) - 75;
	while (j < MINIMAP_HEIGHT)
	{
		i = 0;
		bx = tmpx;
		while (i < MINIMAP_WIDTH)
		{
			if (cub->matrice[by / WALL_DIMENSION][bx / WALL_DIMENSION] == '1' && distance(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, BLACK_MP);
			else if (cub->matrice[by / WALL_DIMENSION][bx / WALL_DIMENSION] != '1' && distance(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, YELLOW_MP);
			i++;
			bx++;
		}
		j++;
		by++;
	}
}

void	cast_allrays(t_cub3d_data *cub)
{
	int		i;

	i = 0;
	cub->data_rays->ray_angle = cub->player_data->rot_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		ray_cast(cub);
		renderwallproject(cub, i);
		cub->data_rays->ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
	put_minimap(cub);
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
				mlx_put_pixel(cub->map_img, x2 * MINIMAP_SCALE_FACTOR, y2 * MINIMAP_SCALE_FACTOR, ORANGE_MP);
			x2++;
		}
		y2++;
	}
}

void	put_minimap(t_cub3d_data *cub)
{
	int	x;
	int	y;

	ft_put_minimap(cub);
	x = 0;
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			if (distance(x, y, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) == 70 || distance(x, y, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) == 71 || distance(x, y, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) == 72)
				mlx_put_pixel(cub->map_img, x, y, ORANGE_MP);
			if (distance(x, y, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) <= 5)
				mlx_put_pixel(cub->map_img, x, y, ORANGE_MP);
			x++;
		}
		y++;
	}
	drawline(cub->map_img, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, cos(cub->player_data->rot_angle + M_PI) * 30+ (MINIMAP_WIDTH/ 2), sin(cub->player_data->rot_angle + M_PI) * 30 + (MINIMAP_HEIGHT / 2), ORANGE_MP);
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
		mlx_put_pixel(cub->map_img, i++, cub->len_j * WALL_DIMENSION - 2, RED_MP);
	j = 0;
	while (j < cub->len_j * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, cub->len_i * WALL_DIMENSION, j++, RED_MP);
	j = 0;
	while (j < cub->len_j * WALL_DIMENSION)
		mlx_put_pixel(cub->map_img, cub->len_i * WALL_DIMENSION - 2, j++, RED_MP);
}

void	put_map(t_cub3d_data *cub)
{
	// int	i;
	// int	j;

	// j = 0;
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cast_allrays(cub);
	// while (cub->matrice[j])
	// {
	// 	i = 0;
	// 	while (cub->matrice[j][i])
	// 	{
	// 		if (cub->matrice[j][i] == '1')
	// 			draw_square(cub->map_img, i * WALL_DIMENSION * MINIMAP_SCALE_FACTOR \
	// 			, j * WALL_DIMENSION * MINIMAP_SCALE_FACTOR \
	// 			, WALL_DIMENSION * MINIMAP_SCALE_FACTOR, WHITE_MP  );
	// 		i++;
	// 	}
	// 	j++;
	// }
	// put_player(cub);
	// mini_map_framing(cub);
}
