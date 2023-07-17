/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:31 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/17 19:26:54 by lsabik           ###   ########.fr       */
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
		draw_square1(cub->map_img, cub->sprites[i].x *  MINIMAP_SCALE_FACTOR, cub->sprites[i].y *  MINIMAP_SCALE_FACTOR, 20 * MINIMAP_SCALE_FACTOR, (cub->sprites[i].visible) ? YELLOW_MP : BLUE_MP);
		i++;
	}
	
}

void    render_vis_sprites(t_cub3d_data *cub, t_sprites *vis_sprites, int vis_sp)
{
	int i;
	int y;
	double sp_height;
	double sp_width;
	double sp_topy;
	double sp_bottomy;
	double sp_angle;
	double sp_screenpos;
	double sp_leftx;
	double sp_rightx;
	t_sprites sprite;

	double texelwidth;
	int text_x;
	int text_y;
	int dist_fromtop;
	unsigned int texelcolor;
	unsigned int *wall_text;

	i = 0;
	while (i < vis_sp)
	{
		sprite = vis_sprites[i];
		
		sp_height = (WALL_DIMENSION / sprite.dist) * DIST_PROJ_PLANE;
		sp_width = sp_height;

		sp_topy = (HEIGHT / 2) - (sp_height / 2);
		if (sp_topy < 0)
			sp_topy = 0;
		sp_bottomy = (HEIGHT / 2) + (sp_height / 2);
		if (sp_bottomy > HEIGHT)
			sp_bottomy = HEIGHT;
		sp_angle = atan2(sprite.y - cub->player_data->y, sprite.x - cub->player_data->x) - cub->player_data->rot_angle;
		sp_angle = normalizeangle(sp_angle);
		sp_screenpos = tan(sp_angle) * DIST_PROJ_PLANE;
		sp_leftx = (WIDTH / 2) + sp_screenpos;
		sp_rightx = sp_leftx + sp_width;
		int x = sp_leftx;
		while (x < sp_rightx)
		{
			texelwidth = (TEXTUR_WIDTH / sp_width);
			text_x = (x - sp_leftx) * texelwidth;
			y = sp_topy;
			while(y < sp_bottomy)
			{
				if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				{
					dist_fromtop = y + (sp_height / 2) - (HEIGHT / 2);
					text_y = dist_fromtop * (TEXTUR_HEIGHT / sp_height);
					wall_text = cub->walltexture[4];
					texelcolor = wall_text[(TEXTUR_WIDTH * text_y) + text_x];
					// printf("dist: %f, %f\n", cub->sprites[i].dist, cub->ray_dist[x]); 
					if (cub->sprites[i].dist < cub->ray_dist[x] && texelcolor != 0xFF00FFFF)
						mlx_put_pixel(cub->map_img, x, y, texelcolor);
				}
				y++;
			}
			x++;
		}
		i++;
	}
}

void    sort_by_distance(t_sprites *vis_sprites, int vis_sp)
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

void render_sprite(t_cub3d_data *cub)
{
	int         i;
	int         vis_sp;
	double      angel_sp_pl;
	t_sprites   vis_sprites[cub->sprite_num];

	i = 0;
	vis_sp = 0;
	while (i < cub->sprite_num)
	{
		angel_sp_pl = cub->player_data->rot_angle - atan2(cub->player_data->y -cub->sprites[i].y, cub->player_data->x -cub->sprites[i].x);
		angel_sp_pl = normalizeangle(angel_sp_pl);
		if (angel_sp_pl > M_PI)
			angel_sp_pl -= M_PI * 2;
		if (angel_sp_pl < -M_PI)
			angel_sp_pl += M_PI * 2;
		angel_sp_pl = fabs(angel_sp_pl);

		if (angel_sp_pl < (FOV_ANGLE / 2) + EPSILON)
		{
			cub->sprites[i].visible = true;
			cub->sprites[i].angle = angel_sp_pl;
			cub->sprites[i].dist = distance_between_points(cub->sprites[i].x, cub->sprites[i].y, cub->player_data->x, cub->player_data->y);
			vis_sprites[vis_sp] = cub->sprites[i];
			vis_sp++;
		}
		else
		{
			cub->sprites[i].visible = false;
		}
		sort_by_distance(vis_sprites, vis_sp);
		//RENDER
		printf("vis_sp: %f\n", cub->sprites[i].dist);
		render_vis_sprites(cub, vis_sprites, vis_sp);
		i++;
	}
}
