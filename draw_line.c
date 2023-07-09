/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:31:03 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/09 14:09:08 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_convert(t_point *a, t_point *b)
{
	int	swap;

	if (a->x > b->x)
	{
			swap = a->x;
			a->x = b->x;
			b->x = swap;
	}
	if (a->y > b->y)
	{
			swap = a->y;
			a->y = b->y;
			b->y = swap;
	}
}

void	drawline(t_cub3d_data *cub, t_point *a, t_point *b, int color)
{
	int	i;
    float steps;
    float xIncrement;
    float yIncrement;

	i = -1;
	a->delta_x = a->x - b->x;
	a->delta_y = a->y - b->y;
	steps = fabs(a->delta_y);
	if (fabs(a->delta_x) > fabs(a->delta_y))
		steps = fabs(a->delta_x);
	xIncrement = (float)(a->delta_x / steps);
	yIncrement = (float)(a->delta_y / steps);
   	while (++i <= steps)
    {
		if (a->x >= 0 &&  a->y >= 0)
     		mlx_put_pixel(cub->map_img, a->x, a->y, color);
        a->x += xIncrement;
        a->y += yIncrement;
    }
	free(a);
	free(b);
}

t_point	*get_points(int x, int y)
{
	t_point		*lines;

	lines = ft_calloc(1, sizeof(t_point));
	if (!lines)
		return (0);
	lines->x = x;
	lines->y = y;
	return (lines);
}
