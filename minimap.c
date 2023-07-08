/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/08 13:33:14 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_square(mlx_image_t *img, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == size - 1 || i == size - 1 || j == 0 || i == 0)
				mlx_put_pixel(img, x + i, y + j, 0x0000000);
			else
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

// void	draw_line(void *mlx_ptr, float x, float y, int color, t_cub3d_data *cub)
// {
// 	int	i;
// 	float x2;
// 	float y2;
//     float dx;
//     float dy;
//     float steps;
//     float xIncrement;
//     float yIncrement;

// 	i = -1;
// 	x2 = x + cos(cub->player_data->rotation_angle) * 20;
// 	y2 = y + sin(cub->player_data->rotation_angle) * 20;
// 	dx = x - x2;
// 	dy = y - y2;
// 	steps = fabs(dy);
// 	if (fabs(dx) > fabs(dy))
// 		steps = fabs(dx);
// 	xIncrement = (float)(dx / steps);
// 	yIncrement = (float)(dy / steps);
//    	while (++i <= steps)
//     {
// 		if (x >= 0 &&  y1 >= 0)
//      		mlx_put_pixel(mlx_ptr, x, y, color);
//         x += xIncrement;
//         y += yIncrement;
//     }
// }

void	cast_allrays(int color, t_cub3d_data *cub)
{
	double	colmnID = 0;
	int		i = 0;

	cub->data_rays->ray_angle  = cub->player_data->rotation_angle - (cub->player_data->fov_angle / 2);
	while (i < cub->player_data->num_rays)
	{
		ray_cast(cub, colmnID);
		// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(cub->player_data->x + cos(cub->player_data->rotation_angle) * 20, cub->player_data->y + sin(cub->player_data->rotation_angle) * 20), ORANGE);
		// draw_line(cub->map_img, cub->player_data->x, cub->player_data->y, color, cub);
		// cub->data_rays->ray_angle += cub->player_data->fov_angle / cub->player_data->num_rays;
		i++;
		colmnID++;
	}
}

int	distance(int i, int j, int x, int y)
{
	return (sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

void	put_player(t_cub3d_data *cub)
{
	int	x2;
	int	y2;

	x2 = 0;
	y2 = 0;
	while (y2 < cub->len_j * 20)
	{
		x2 = 0;
		while (x2 < cub->len_i * 20)
		{
			if (distance(x2, y2, cub->player_data->x, cub->player_data->y) \
				<= cub->player_data->radius)
				mlx_put_pixel(cub->map_img, x2, y2, 0xFF7000FF);
			x2++;
		}
		y2++;
	}
	// draw_line(cub->map_img, cub->player_data->x, cub->player_data->y, ORANGE, cub);
	cast_allrays(0xFF0000FF, cub);
}

void	mini_map_framing(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->len_i * 20)
		mlx_put_pixel(cub->map_img, i++, j, 0xFF0000FF);
	i = 0;
	while (i < cub->len_i * 20)
		mlx_put_pixel(cub->map_img, i++, cub->len_j * 20 - 1, 0xFF0000FF);
	j = 0;
	while (j < cub->len_j * 20)
		mlx_put_pixel(cub->map_img, cub->len_i * 20, j++, 0xFF0000FF);
	j = 0;
	while (j < cub->len_j * 20)
		mlx_put_pixel(cub->map_img, cub->len_i * 20 - 1, j++, 0xFF0000FF);
}

void	put_map(t_cub3d_data *cub)
{
	int	i;
	int	j;

	j = 0;
	cub->map_img = mlx_new_image(cub->mlx, cub->len_i * 20, cub->len_j * 20);
	while (cub->matrice[j])
	{
		i = 0;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == '1')
				draw_square(cub->map_img, i * 20, j * 20, 20, 0xFFFFFFFF);
			i++;
		}
		j++;
	}
	put_player(cub);
	mini_map_framing(cub);
}

void	ray_cast(t_cub3d_data *cub, double colmnID)
{
	double	yintercept;
	double	xintercept;
	double	ystep;
	double	xstep;
	double	nextHorztouchX; 
	double	nextHorztouchY;
	double	foundhorzwallhit;
	double	wallhitX;
	double	wallhitY;

	foundhorzwallhit = 0;
	yintercept = floor(cub->player_data->y / 20) * 20;
	if (cub->data_rays->is_rayfacingdown)
		yintercept += 20;
	xintercept = cub->player_data->x * (yintercept - cub->player_data->y) / tan(cub->data_rays->ray_angle); 
	yintercept += floor(cub->player_data->x / 20) * 20;
	ystep = 20;
	if (cub->data_rays->is_rayfacingup)
		ystep *= -1;
	xstep = 20 / tan(cub->data_rays->ray_angle);
	if (cub->data_rays->is_rayfacingileft && xstep > 0)
		xstep *= -1;
	if (cub->data_rays->is_rayfacingright && xstep < 0)
		xstep *= -1;
	nextHorztouchX = xintercept;
	nextHorztouchY = yintercept;
	if (cub->data_rays->is_rayfacingup)
		nextHorztouchY--;
	while (nextHorztouchX >= 0 && nextHorztouchX <= 20 * cub->len_i && nextHorztouchY >= 0 && nextHorztouchY <= 20 * cub->len_j)
	{
		if (cub->matrice[(int)(nextHorztouchX / 20)][(int)(nextHorztouchY / 20)] == '1')
		{
			foundhorzwallhit = 1;
			wallhitX = nextHorztouchX;
			wallhitY = nextHorztouchY;
			drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(wallhitX, wallhitY), ORANGE);
			// ft_line(x, y, wallhitX, wallhitY, );
			break ;
		}
		else
		{
			nextHorztouchX += xstep;
			nextHorztouchX += ystep;
		}
	}
	// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(wallhitX, wallhitY), ORANGE);
}