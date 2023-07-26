/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/26 23:22:59 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

	if (cub->anim_flag == 18)
		cub->anim_flag = 5;
	if (cub->walk_flag == 13)
		cub->walk_flag = 0;
	else
	{
		i++;
		if (i == 2)
		{
			i = 0;
			cub->anim_flag++;
			cub->walk_flag++;
		}
	}
}
