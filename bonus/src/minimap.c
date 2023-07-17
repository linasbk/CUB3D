/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/17 18:39:02 by lsabik           ###   ########.fr       */
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
	// cub->rays->ray_ang = cub->player_data->rot_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		cub->rays->ray_ang = cub->player_data->rot_angle + atan((i - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		ray_cast(cub);
		renderwallproject(cub, i);
		cub->rays->ray_ang += FOV_ANGLE / NUM_RAYS;
		cub->ray_dist[i] = cub->rays->distance;
		i++;
	}
}

int	distance(int i, int j, int x, int y)
{
	return (sqrt(pow(x - i, 2) + pow(y - j, 2)));
}
void	draw_square(mlx_image_t *img, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size + 1)
	{
		j = 0;
		while (j < size + 1)
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

void	cub_img(t_cub3d_data *cub)
{
	int	i;
	int	j;

	j = 0;
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cast_allrays(cub);
	while (cub->matrice[j])
	{
		i = 0;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == '1')
				draw_square(cub->map_img, i * WALL_DIMENSION * MINIMAP_SCALE_FACTOR \
				, j * WALL_DIMENSION * MINIMAP_SCALE_FACTOR \
				, WALL_DIMENSION * MINIMAP_SCALE_FACTOR, WHITE_MP  );
			i++;
		}
		j++;
	}
	put_player(cub);
	find_sprites(cub);
	render_sprite(cub);
	render_mapsprites(cub);
	// put_mini_map(cub);
}
