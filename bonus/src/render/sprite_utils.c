/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:04:59 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/21 17:30:53 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square1(mlx_image_t *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

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

void	find_coordinates(t_cub3d_data *cub)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (cub->matrice[j])
	{
		i = 0;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == 'Y')
			{
				cub->sprites[k].x = i * WALL_DIMENSION;
				cub->sprites[k].y = j * WALL_DIMENSION;
				k++;
			}
			i++;
		}
		j++;
	}
}

void	find_sprites(t_cub3d_data *cub, int i, int j, int n)
{
	while (cub->matrice[j])
	{
		i = 0;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == 'Y')
				n++;
			i++;
		}
		j++;
	}
	cub->sp = ft_calloc(1, sizeof(t_spinfos));
	cub->sprites = (t_sprites*)malloc(n * sizeof(t_sprites));
	if (!cub->sprites)
	{
		puts("Memory allocation failed!\n");
		exit(FAILURE);
	}
	cub->sprite_num = n;
	find_coordinates(cub);
}

void	calc_sprite_dims(t_cub3d_data *cub, t_sprites sprite)
{
	cub->sp->correct_dist = sprite.dist * cos(sprite.angle);
	cub->sp->sp_height = (WALL_DIMENSION / cub->sp->correct_dist) \
		* cub->d_pr_plane;
	cub->sp->sp_width = cub->sp->sp_height;
	cub->sp->sp_topy = (HEIGHT / 2) - (cub->sp->sp_height / 2);
	if (cub->sp->sp_topy < 0)
		cub->sp->sp_topy = 0;
	cub->sp->sp_bottomy = (HEIGHT / 2) + (cub->sp->sp_height / 2);
	if (cub->sp->sp_bottomy > HEIGHT)
		cub->sp->sp_bottomy = HEIGHT;
	cub->sp->sp_angle = atan2(sprite.y - cub->player->y, sprite.x \
		- cub->player->x) - cub->player->rot_angle;
	cub->sp->sp_angle = normalizeangle(cub->sp->sp_angle);
	cub->sp->sp_screenpos = tan(cub->sp->sp_angle) * cub->d_pr_plane;
	cub->sp->sp_leftx = (WIDTH / 2) + cub->sp->sp_screenpos - \
		(cub->sp->sp_width / 2);
	cub->sp->sp_rightx = cub->sp->sp_leftx + cub->sp->sp_width;
}

// void    render_mapsprites(t_cub3d_data *cub)
// {
// 	int i;

// 	i = 0;
// 	while (i < cub->sprite_num)
// 	{
// 		draw_square1(cub->map_img, cub->sprites[i].x *  MINIMAP_SCALE_FACTOR, cub->sprites[i].y *  MINIMAP_SCALE_FACTOR, 64 * MINIMAP_SCALE_FACTOR, (cub->sprites[i].visible) ? YELLOW_MP : BLUE_MP);
// 		i++;
// 	}
// }
