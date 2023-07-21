/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:00:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/21 19:02:33 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calcs_offset_x(t_cub3d_data *cub, int x, int *first)
{
	cub->sp->texelwidth = (cub->text[*first]->width / cub->sp->sp_width);
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

void	calcs_offset_y(t_cub3d_data *cub, int y, int *first)
{
	cub->sp->dist_fromtop = y + (cub->sp->sp_height / 2) - (HEIGHT / 2);
	cub->sp->text_y = cub->sp->dist_fromtop * \
		(cub->text[*first]->height / cub->sp->sp_height);
}

void	sprites_animation(int *first)
{
	if (*first == 4)
		*first = 4;
	else
		(*first)++;
}
