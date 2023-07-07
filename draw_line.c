/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:31:03 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/07 22:43:30 by nouahidi         ###   ########.fr       */
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

void	drawline(t_cub3d_data *cub, t_point *a, t_point *b)
{
	int	p;
	int	color;

	ft_convert(a, b);
	color = cub->color;
	a->delta_x = b->x - a->x;
	a->delta_y = b->y - a->y;
	p = sqrt((a->delta_x * a->delta_x) + (a->delta_y * a->delta_y));
	a->delta_x /= p;
	a->delta_y /= p;
	while (p)
	{
		if ((a->x > 0 && a->x < WIDTH) && (a->y > 0
				&& a->y < HEIGHT))
            // mlx_put_pixel(image, x, y, color);
			my_mlx_pixel_put(cub, a->x, a->y, color);
			a->x += a->delta_x;
			a->y += a->delta_y;
			--p;
	}
	free(a);
	free(b);
}
t_point	*get_points(int x, int y)
{
	t_point		*lines;

	lines = malloc(sizeof(t_point));
	if (!lines)
		return (0);
	lines->x = x;
	lines->y = y;
	return (lines);
}

// void	draw(t_cub3d_data *cub)
// {
// 	drawline(cub, get_points(x, y), get_points(x, y + 1));
// 	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0,0);
// }