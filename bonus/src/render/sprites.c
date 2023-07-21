/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:31 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/21 17:31:56 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_vis_sprites(t_cub3d_data *cub, t_sprites *vis_sprites, int vis_sp, int *first)
{
	int				i;
	int				y;
	int				x;
	t_sprites		sprite;
	unsigned int	texelcolor;
	unsigned int	*wall_text;

	i = 0;
	while (i < vis_sp)
	{
		sprite = vis_sprites[i];
		calc_sprite_dims(cub, sprite);
		x = cub->sp->sp_leftx;
		while (x < cub->sp->sp_rightx)
		{
			cub->sp->texelwidth = (cub->text[4]->width / cub->sp->sp_width);
			cub->sp->text_x = (x - cub->sp->sp_leftx) * cub->sp->texelwidth;
			y = cub->sp->sp_topy;
			while (y < cub->sp->sp_bottomy)
			{
				if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				{
					cub->sp->dist_fromtop = y + (cub->sp->sp_height / 2) - \
						(HEIGHT / 2);
					cub->sp->text_y = cub->sp->dist_fromtop * \
						(cub->text[4]->height / cub->sp->sp_height);
					if (sprite.dist < cub->ray_dist[x])
					{
						wall_text = cub->walltexture[4];
						if (((cub->text[4]->width * cub->sp->text_y) + \
							cub->sp->text_x) > 0 && ((cub->text[4]->width * \
							cub->sp->text_y) + cub->sp->text_x) < \
							(cub->text[4]->width * cub->text[4]->height))
						{
							texelcolor = wall_text[(cub->text[4]->width * \
							cub->sp->text_y) + cub->sp->text_x];
							if (texelcolor != 0)
								mlx_put_pixel(cub->map_img, x, y, texelcolor);
						}
					}
				}
				y++;
			}
			x++;
		}
		i++;
	}
	if (*first == 4)
		*first = 4;
	else
		(*first)++;
}

void	sort_by_distance(t_sprites *vis_sprites, int vis_sp)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < vis_sp)
	{
		j = i + 1;
		while (j < vis_sp)
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
	int			vis_sp;
	double		angel_sp_pl;
	static int	first;
	t_sprites	vis_sprites[cub->sprite_num];

	vis_sp = 0;
	first = 4;
	while (i < cub->sprite_num)
	{
		cub->sprites[i].dist = 0;
		angel_sp_pl = cub->player->rot_angle - atan2(cub->player->y - \
			cub->sprites[i].y, cub->player->x - cub->sprites[i].x);
		norm_angle(&angel_sp_pl);
		if (angel_sp_pl < (FOV_ANGLE / 2) + EPSILON)
		{
			cub->sprites[i].visible = true;
			cub->sprites[i].angle = angel_sp_pl;
			cub->sprites[i].dist = distance_between_points(cub->sprites[i].x, \
				cub->sprites[i].y, cub->player->x, cub->player->y);
			vis_sprites[vis_sp] = cub->sprites[i];
			vis_sp++;
		}
		else
			cub->sprites[i].visible = false;
		sort_by_distance(vis_sprites, vis_sp);
		render_vis_sprites(cub, vis_sprites, vis_sp, &first);
		i++;
	}
}
