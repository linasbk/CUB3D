/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:47:32 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/09 20:44:50 by lsabik           ###   ########.fr       */
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

void	cast_allrays(int color, t_cub3d_data *cub)
{
	float	colmnID = 0;
	int		i = 0;
	
	cub->data_rays->ray_angle  = cub->player_data->rotation_angle;
	while (i < cub->player_data->num_rays)
	{
		cub->data_rays->ray_angle = normalizeamgle(cub->data_rays->ray_angle);
		// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(cub->player_data->x + cos(cub->player_data->rotation_angle) * 20, cub->player_data->y + sin(cub->player_data->rotation_angle) * 20), ORANGE);

	  //////////////////////////////////////////
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

int	protect_matrice(float nextHorztouchX, float nextHorztouchY, t_cub3d_data *cub)
{
	int	x;
	int	y;

	x = floor(nextHorztouchX / 20);
	y = floor(nextHorztouchY / 20);
	if (x < 0 || x >= cub->len_i - 1 || y < 0 || y >= cub->len_j - 1)
		return (1);
	return(cub->matrice[y][x] == '1');
}

int distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	raycast_init(t_cub3d_data *cub, float colmnID)
{
	// if (cub->data_rays->ray_angle > 0 && cub->data_rays->ray_angle < M_PI)
	// 	cub->data_rays->is_rayfacingdown = 1;
	// if (cub->data_rays->ray_angle < M_PI / 2 \
	// 	|| cub->data_rays->ray_angle > (3 * M_PI) / 2)
	// 	cub->data_rays->is_rayfacingright = 1;
	
	if (cub->data_rays->ray_angle > M_PI)
	{
		cub->data_rays->is_rayfacingup = 0;
		cub->data_rays->is_rayfacingdown = 1;
	}
	else
	{
		cub->data_rays->is_rayfacingdown = 0;
		cub->data_rays->is_rayfacingup = 1;
	}
	if (cub->data_rays->ray_angle > M_PI / 2 \
		&& cub->data_rays->ray_angle < (3 * M_PI) / 2)
	{
		cub->data_rays->is_rayfacingleft = 0;
		cub->data_rays->is_rayfacingright = 1;
	}
	else
	{
		cub->data_rays->is_rayfacingright = 0;
		cub->data_rays->is_rayfacingleft = 1;
	}
}

void	 ray_cast(t_cub3d_data *cub, float colmnID)
{	
	float	wallhitX = 0;
	float	wallhitY = 0;
	float	distance = 0;
	float	wasHitVertical = 0;
	float	yintercept;
	float	xintercept;
	float	ystep;
	float	xstep;
	float	nextHorztouchX; 
	float	nextHorztouchY;
	int		foundhorzwallhit;
	float	hor_wallhitX = 0;
	float	hor_wallhitY = 0;
	
	raycast_init(cub, colmnID);

	// cub->data_rays->ray_angle  = cub->player_data->rotation_angle - (cub->player_data->fov_angle / 2);
	// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(cub->player_data->x + cos(cub->player_data->rotation_angle) * 20, cub->player_data->y + sin(cub->player_data->rotation_angle) * 20), ORANGE);
	  //////////////////////////////////////////
	 // HORIZONTAL RAY-GRID INTERSECTION CODE//
	//////////////////////////////////////////
	 
	yintercept = floor(cub->player_data->y / 20) * 20;
	if (cub->data_rays->is_rayfacingdown)
		yintercept += 20;
	xintercept = cub->player_data->x + (yintercept - cub->player_data->y) / tan(cub->data_rays->ray_angle);
	ystep = 20;
	xstep = 20 / tan(cub->data_rays->ray_angle);
	if (cub->data_rays->is_rayfacingup)
		ystep *= -1;
	if (cub->data_rays->is_rayfacingleft && xstep > 0)
		xstep *= -1;
	if (cub->data_rays->is_rayfacingright && xstep < 0)
		xstep *= -1;
	nextHorztouchX = xintercept;
	nextHorztouchY = yintercept;
	if (cub->data_rays->is_rayfacingup)
		nextHorztouchY--;
	// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(cub->player_data->x + cos(cub->player_data->rotation_angle) * 20, cub->player_data->y + sin(cub->player_data->rotation_angle) * 20), ORANGE);
	while (nextHorztouchX >= 0 && nextHorztouchX <= 20 * cub->len_i && nextHorztouchY >= 0 && nextHorztouchY <= 20 * cub->len_j)
	{
		if (protect_matrice(nextHorztouchX, nextHorztouchY, cub))
		{
			foundhorzwallhit = 1;
			hor_wallhitX = nextHorztouchX;
			hor_wallhitY = nextHorztouchY;
			break ;
		}
		else
		{
			nextHorztouchX += xstep;
			nextHorztouchY += ystep;
		}
	}
	// drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(hor_wallhitX, hor_wallhitY), ORANGE);
	  //////////////////////////////////////////
	 //  VERTICAL RAY-GRID INTERSECTION CODE //
	//////////////////////////////////////////
	int		foundverzwallhit = 0;
	float	vert_wallhitX = 0;
	float	vert_wallhitY = 0;
	float	nextvert_touchX;
	float	nextvert_touchY;

	xintercept = floor(cub->player_data->x / 20) * 20;
	if (cub->data_rays->is_rayfacingright)
		xintercept += 20;
	yintercept = cub->player_data->y + (xintercept - cub->player_data->x) * tan(cub->data_rays->ray_angle);
	xstep = 20;
	if (cub->data_rays->is_rayfacingleft)
		xstep *= -1;
	ystep = 20 * tan(cub->data_rays->ray_angle);
	if (cub->data_rays->is_rayfacingup && ystep > 0)
		ystep *= -1;
	if (cub->data_rays->is_rayfacingdown && ystep < 0)
		ystep *= -1;
	nextvert_touchX = xintercept;
	nextvert_touchY = yintercept;
	if (cub->data_rays->is_rayfacingleft)
		nextvert_touchX--;
	while (nextvert_touchX >= 0 && nextvert_touchX <= 20 * cub->len_i && nextvert_touchY >= 0 && nextvert_touchY <= 20 * cub->len_j)
	{
		if (protect_matrice(nextvert_touchX, nextvert_touchY, cub))
		{
			foundverzwallhit = 1;
			vert_wallhitX = nextvert_touchX;
			vert_wallhitY = nextvert_touchY;
			break ;
		}
		else
		{
			nextvert_touchX += xstep;
			nextvert_touchY += ystep;
		}
	}
	//calculate hor and ver distance and choose the smallest one
	int horzhitdistance = INT_MAX;
	
	if (foundhorzwallhit)
		horzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, hor_wallhitX, hor_wallhitY);
	int vertzhitdistance = INT_MAX;
	if (foundverzwallhit)
		vertzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, vert_wallhitX, vert_wallhitY);
	if (vertzhitdistance > horzhitdistance)
		wallhitX = hor_wallhitX;
	else
		wallhitX = vert_wallhitX;
	if (vertzhitdistance > horzhitdistance)
		wallhitY = hor_wallhitY;
	else
		wallhitY = vert_wallhitY;
	if (vertzhitdistance > horzhitdistance)
		distance = horzhitdistance;
	else
		distance = vertzhitdistance;
	if (vertzhitdistance < horzhitdistance)
		wasHitVertical = 1;
	else
		wasHitVertical = 0;

	drawline(cub, get_points(cub->player_data->x, cub->player_data->y), get_points(wallhitX, wallhitY), ORANGE);
}