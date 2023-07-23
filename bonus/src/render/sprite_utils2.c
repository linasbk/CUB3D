/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/22 19:09:37 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calcs_offset_x(t_cub3d_data *cub, int x)
{
	cub->sp->texelwidth = (cub->text[cub->anim_flag]->width / cub->sp->sp_width);
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

void	calcs_offset_y(t_cub3d_data *cub, int y)
{
	cub->sp->dist_fromtop = y + (cub->sp->sp_height / 2) - (HEIGHT / 2);
	cub->sp->text_y = cub->sp->dist_fromtop * \
		(cub->text[cub->anim_flag]->height / cub->sp->sp_height);
}

void	sprites_animation(t_cub3d_data *cub)
{
	static int	i;

	if (cub->anim_flag == 14)
		cub->anim_flag = 5;
	else
	{
		i++;
		if (i == 5)
		{
			i = 0;
			cub->anim_flag++;
		}
	}
}
