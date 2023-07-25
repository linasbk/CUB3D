/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:04:59 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/25 14:57:32 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			if (sprites_char(cub->matrice[j][i]))
			{
				cub->sprites[k].x = (i * W_DM) + 32;
				cub->sprites[k].y = (j * W_DM) + 32;
				if (cub->matrice[j][i] == 'Y')
				{
					cub->sprites[k].sp_text = cub->text[cub->anim_flag];
					cub->sprites[k].index = cub->anim_flag;
				}
				else if (cub->matrice[j][i] == 'T')
				{
					cub->sprites[k].sp_text = cub->text[20];
					cub->sprites[k].index = 20;
				}
				else if (cub->matrice[j][i] == 'y')
				{
					cub->sprites[k].sp_text = cub->text[19];
					cub->sprites[k].index = 19;
				}
				// else if (cub->matrice[j][i] == 'L')
				// {
				// 	cub->sprites[k].sp_text = cub->text[22];
				// 	cub->sprites[k].index = 22;
				// }
				// else if (cub->matrice[j][i] == 'l')
				// {
				// 	cub->sprites[k].sp_text = cub->text[21];
				// 	cub->sprites[k].index = 21;
				// }
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
			if (cub->matrice[j][i] == 'Y' || cub->matrice[j][i] == 'T' || cub->matrice[j][i] == 'y')
				n++;
			i++;
		}
		j++;
	}
	cub->sp = ft_calloc(1, sizeof(t_spinfos));
	cub->sprites = (t_sprites *)malloc(n * sizeof(t_sprites));
	if (!cub->sprites)
	{
		puts("Memory allocation failed!\n");
		exit(FAILURE);
	}
	cub->sprite_num = n;
	find_coordinates(cub);
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

void	calc_sprite_dims(t_cub3d_data *cub, t_sprites sprite)
{
	cub->sp->correct_dist = sprite.dist * cos(sprite.angle);
	cub->sp->sp_height = (W_DM / cub->sp->correct_dist) \
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
	cub->sp->sp_screen_imgpos = tan(cub->sp->sp_angle) * cub->d_pr_plane;
	cub->sp->sp_leftx = (WIDTH / 2) + cub->sp->sp_screen_imgpos - \
		(cub->sp->sp_width / 2);
	cub->sp->sp_rightx = cub->sp->sp_leftx + cub->sp->sp_width;
}

void	draw_sprites(t_cub3d_data *cub, t_sprites *vis_sprites, int vis_sp)
{
	int	i;

	i = -1;
	while (++i < cub->sprite_num)
	{
		sort_by_distance(vis_sprites, vis_sp);
		render_vis_sprites(cub, vis_sprites, vis_sp, i);
	}
	free(vis_sprites);
	free(cub->sprites);
	free(cub->sp);
}
