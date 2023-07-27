/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/27 13:57:21 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fixed_sprites(t_cub3d_data *cub, int i, int j, int k)
{
	if (cub->matrice[j][i] == 'T')
	{
		cub->sprites[k].sp_text = cub->text[20];
		cub->sprites[k].index = 20;
	}
	else if (cub->matrice[j][i] == 'y')
	{
		cub->sprites[k].sp_text = cub->text[19];
		cub->sprites[k].index = 19;
	}
	else if (cub->matrice[j][i] == 'L')
	{
		cub->sprites[k].sp_text = cub->text[22];
		cub->sprites[k].index = 22;
	}
	else if (cub->matrice[j][i] == 'l')
	{
		cub->sprites[k].sp_text = cub->text[21];
		cub->sprites[k].index = 21;
	}
}

void	calcs_offset_x(t_cub3d_data *cub, int x, mlx_texture_t *sp_text)
{
	cub->sp->texelwidth = (sp_text->width / cub->sp->sp_width);
	cub->sp->text_x = (x - cub->sp->sp_leftx) * cub->sp->texelwidth;
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

void	calcs_offset_y(t_cub3d_data *cub, int y, mlx_texture_t *sp_text)
{
	cub->sp->dist_fromtop = y + (cub->sp->sp_height / 2) - (HEIGHT / 2);
	cub->sp->text_y = cub->sp->dist_fromtop * \
		(sp_text->height / cub->sp->sp_height);
}

void	sprites_animation(t_cub3d_data *cub)
{
	static int	i;

	if (cub->anim_flag == 24)
		cub->anim_flag = 5;
	if (cub->walk_flag == 13)
		cub->walk_flag = 0;
	else
	{
		i++;
		if (i == 3)
		{
			i = 0;
			cub->anim_flag++;
			cub->walk_flag++;
		}
	}
}
