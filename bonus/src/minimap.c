/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/15 18:16:45 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_put_minimap(t_cub3d_data *cub)
{
	int	i;
	int	j;
	int	bx;
	int	by;
	int	tmpx;

	i = 0;
	j = 0;
	bx = (cub->player_data->x) - 75;
	tmpx = bx;
	by = (cub->player_data->y) - 75;
	if (bx < 0 || by < 0)
	{
		if (bx < 0)
		{
			i = (bx * -1);
			bx = 0;
		}
		else
		{
			j = (by * -1);
			by = 0;
		}
	}
	while (j < MINIMAP_HEIGHT)
	{
		i = 0;
		bx = tmpx;
		while (i < MINIMAP_WIDTH)
		{
			if ((by / WALL_DIMENSION) < cub->len_j)
			{
				if (cub->matrice[by / WALL_DIMENSION][bx / WALL_DIMENSION] == '1' && distance(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, i, j) < 70)
					mlx_put_pixel(cub->map_img, i, j, get_color(0, 0, 0, 50));
				else if (cub->matrice[by / WALL_DIMENSION][bx / WALL_DIMENSION] != '1' && distance(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, i, j) < 70)
					mlx_put_pixel(cub->map_img, i, j, get_color(255, 255, 0, get_color(255, 255, 0, 50)));
			}
			i++;
			bx++;
		}
		j++;
		by++;
	}
}

void	put_mini_map(t_cub3d_data *cub)
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

void	cast_allrays(t_cub3d_data *cub)
{
	int		i;

	i = 0;
	cub->rays->ray_ang = cub->player_data->rot_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		ray_cast(cub);
		renderwallproject(cub, i);
		cub->rays->ray_ang += FOV_ANGLE / NUM_RAYS;
		i++;
	}
	put_mini_map(cub);
}

int	distance(int i, int j, int x, int y)
{
	return (sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

void	cub_img(t_cub3d_data *cub)
{
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cast_allrays(cub);
}
