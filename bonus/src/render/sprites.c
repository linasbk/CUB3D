/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:31 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/21 14:45:43 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square1(mlx_image_t *img, int x, int y, int size, int color)
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

void    find_coordinates(t_cub3d_data *cub)
{
	int i;
	int j;
	int k;

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

void    find_sprites(t_cub3d_data *cub)
{
	int i = 0;
	int j = 0;
	int n = 0;

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
	cub->sp = ft_calloc(1,sizeof(t_spinfos));
	cub->sprites = (t_sprites*)malloc(n * sizeof(t_sprites));
	if (!cub->sprites)
	{
		puts("Memory allocation failed!\n");
		exit(FAILURE);
	}
	cub->sprite_num = n;
	find_coordinates(cub);
}

void    render_mapsprites(t_cub3d_data *cub)
{
	int i;

	i = 0;
	while (i < cub->sprite_num)
	{
		draw_square1(cub->map_img, cub->sprites[i].x *  MINIMAP_SCALE_FACTOR, cub->sprites[i].y *  MINIMAP_SCALE_FACTOR, 64 * MINIMAP_SCALE_FACTOR, (cub->sprites[i].visible) ? YELLOW_MP : BLUE_MP);
		i++;
	}
	
}

void	calc_sprite_dims(t_cub3d_data *cub, t_sprites sprite)
{
	cub->sp->correct_dist = sprite.dist * cos(sprite.angle);
	cub->sp->sp_height = (WALL_DIMENSION / cub->sp->correct_dist) * cub->d_pr_plane;
	cub->sp->sp_width = cub->sp->sp_height;
	cub->sp->sp_topy = (HEIGHT / 2) - (cub->sp->sp_height / 2);
	if (cub->sp->sp_topy < 0)
		cub->sp->sp_topy = 0;
	cub->sp->sp_bottomy = (HEIGHT / 2) + (cub->sp->sp_height / 2);
	if (cub->sp->sp_bottomy > HEIGHT)
		cub->sp->sp_bottomy = HEIGHT;
	cub->sp->sp_angle = atan2(sprite.y - cub->player->y, sprite.x - cub->player->x) - cub->player->rot_angle;
	cub->sp->sp_angle = normalizeangle(cub->sp->sp_angle);
	cub->sp->sp_screenpos = tan(cub->sp->sp_angle) * cub->d_pr_plane;
	cub->sp->sp_leftx = (WIDTH / 2) + cub->sp->sp_screenpos - (cub->sp->sp_width / 2);
	cub->sp->sp_rightx = cub->sp->sp_leftx + cub->sp->sp_width;
}

void	render_vis_sprites(t_cub3d_data *cub, t_sprites *vis_sprites, int vis_sp)
{
	int i;
	int y;
	int x;
	t_sprites sprite;
	unsigned int texelcolor;
	unsigned int *wall_text;

	i = 0;
	while (i < vis_sp)
	{
		sprite = vis_sprites[i];
		calc_sprite_dims(cub, sprite);
		x = cub->sp->sp_leftx;
		while (x < cub->sp->sp_rightx)
		{
			cub->sp->texelwidth = (TEXTUR_WIDTH / cub->sp->sp_width);
			cub->sp->text_x = (x - cub->sp->sp_leftx) * cub->sp->texelwidth;
			y = cub->sp->sp_topy;
			while(y < cub->sp->sp_bottomy)
			{
				if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				{
					cub->sp->dist_fromtop = y + (cub->sp->sp_height / 2) - (HEIGHT / 2);
					cub->sp->text_y = cub->sp->dist_fromtop * (TEXTUR_HEIGHT / cub->sp->sp_height);
					// int i = 4;
					// while (i < 8)
					// {
						if (sprite.dist < cub->ray_dist[x])
						{
							wall_text = cub->walltexture[4];
							texelcolor = wall_text[(TEXTUR_WIDTH * cub->sp->text_y) + cub->sp->text_x];
						 	if (texelcolor != 0x00000000)
								mlx_put_pixel(cub->map_img, x, y, texelcolor);
						}
					// 	i++;
					// }
				}
				y++;
			}
			x++;
		}
		i++;
	}
}

void	sort_by_distance(t_sprites *vis_sprites, int vis_sp)
{
	int i;
	int j;
	t_sprites temp;

	i = 0;
	while (i < vis_sp)
	{
		j = i + 1;
		while(j < vis_sp)
		{
			if (vis_sprites[i].dist < vis_sprites[j].dist)
			{
				temp = vis_sprites[i];
				vis_sprites[i] = vis_sprites[j];
				vis_sprites[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	norm_angle(double *angle)
{
	*angle = normalizeangle(*angle);
	if (*angle > M_PI)
		*angle -= M_PI * 2;
	if (*angle < -M_PI)
		*angle += M_PI * 2;
	*angle = fabs(*angle);
}

void	render_sprite(t_cub3d_data *cub, int i)
{
	int         vis_sp;
	double      angel_sp_pl;
	t_sprites   vis_sprites[cub->sprite_num];

	vis_sp = 0;
	while (i < cub->sprite_num)
	{
		cub->sprites[i].dist = 0;
		angel_sp_pl = cub->player->rot_angle - atan2(cub->player->y -cub->sprites[i].y, cub->player->x -cub->sprites[i].x);
		norm_angle(&angel_sp_pl);
		if (angel_sp_pl < (FOV_ANGLE / 2) + EPSILON)
		{
			cub->sprites[i].visible = true;
			cub->sprites[i].angle = angel_sp_pl;
			cub->sprites[i].dist = distance_between_points(cub->sprites[i].x, cub->sprites[i].y, cub->player->x, cub->player->y);
			vis_sprites[vis_sp] = cub->sprites[i];
			vis_sp++;
		}
		else
			cub->sprites[i].visible = false;
		sort_by_distance(vis_sprites, vis_sp);
		render_vis_sprites(cub, vis_sprites, vis_sp);
		i++;
	}
}
