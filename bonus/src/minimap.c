/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/22 16:37:45 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_puts_pixel(t_cub3d_data *cub, int by, int tmpx, int j)
{
	int		i;
	int		bx;

	i = cub->tmpi - 1;
	bx = tmpx;
	while (i < MP_WIDTH)
	{
		if ((by / (W_DM / 2)) < cub->len_j)
		{
			if (check_ch(cub, bx, by, '1') && distance(MP_WIDTH / 2, \
				MP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, WHITE_MP);
			else if (check_ch(cub, bx, by, 'D') && distance(MP_WIDTH / 2, \
				MP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, BLACK_MP);
			else if (check_ch(cub, bx, by, 'Y') && distance(MP_WIDTH / 2, \
				MP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, PURPLE_MP);
			else if (check_ch(cub, bx, by, 'd') && distance(MP_WIDTH / 2, \
				MP_HEIGHT / 2, i, j) < 70)
				mlx_put_pixel(cub->map_img, i, j, YELLOW_MP);
		}
		bx++;
		i++;
	}
}

void	ft_put_minimap(t_cub3d_data *cub)
{
	int		j;
	int		bx;
	int		by;

	j = 0;
	bx = (cub->player->x / 2) - 75;
	by = (cub->player->y / 2) - 75;
	if (bx < 0)
	{
		cub->tmpi = (bx * -1);
		bx = 0;
	}
	else
	{
		j = (by * -1);
		by = 0;
	}
	while (j < MP_HEIGHT)
	{
		ft_puts_pixel(cub, by, bx, j);
		by++;
		j++;
	}
}

void	put_mini_map(t_cub3d_data *cub)
{
	int	x;
	int	y;

	ft_put_minimap(cub);
	y = 0;
	while (y < MP_HEIGHT)
	{
		x = 0;
		while (x < MP_WIDTH)
		{
			if (distance(x, y, MP_WIDTH / 2, MP_HEIGHT / 2) == 70 \
			|| distance(x, y, MP_WIDTH / 2, MP_HEIGHT / 2) == 71 || \
			distance(x, y, MP_WIDTH / 2, MP_HEIGHT / 2) == 72)
				mlx_put_pixel(cub->map_img, x, y, ORANGE_MP);
			if (distance(x, y, MP_WIDTH / 2, MP_HEIGHT / 2) <= 5)
				mlx_put_pixel(cub->map_img, x, y, ORANGE_MP);
			x++;
		}
		y++;
	}
	drawline(cub, cos(cub->player->rot_angle + M_PI) * 30 + \
	(MP_WIDTH / 2), sin(cub->player->rot_angle + M_PI) * 30 \
	+ (MP_HEIGHT / 2));
}

void	cast_allrays(t_cub3d_data *cub)
{
	int		i;

	i = 0;
	while (i < NUM_RAYS)
	{
		cub->rays->ray_ang = cub->player->rot_angle + \
		atan((i - NUM_RAYS / 2) / cub->d_pr_plane);
		ray_cast(cub, INT_MAX, INT_MAX);
		renderwallproject(cub, i, index_dir(cub));
		cub->rays->ray_ang += FOV_ANGLE / NUM_RAYS;
		cub->ray_dist[i] = cub->rays->distance;
		i++;
	}
}

void	cub_img(t_cub3d_data *cub)
{
	int	j;

	j = 0;
	cub->rays->flag = 0;
	// cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->map_img)
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	exit(EXIT_FAILURE);
	// }
	cast_allrays(cub);
	find_sprites(cub, 0, 0, 0);
	render_sprite(cub, -1);
	put_mini_map(cub);
}
