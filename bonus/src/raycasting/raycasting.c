/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:59:00 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/20 18:39:11 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_content(t_cub3d_data *cub, int i, int j)
{
	int	x;
	int	y;

	x = floor(i / WALL_DIMENSION);
	y = floor(j / WALL_DIMENSION);
	if (x < 0 || x > cub->len_i || y < 0 || y > cub->len_j - 1)
		return (1);
	return ((int)cub->matrice[y][x]);
}

void	add_door(t_cub3d_data *cub, char c1, char c2)
{
	if (cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) + 1] \
		[(int)cub->player_data->x / WALL_DIMENSION] == c1)
		cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) + 1] \
			[(int)cub->player_data->x / WALL_DIMENSION] = c2;
	else if (cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) - 1] \
		[(int)cub->player_data->x / WALL_DIMENSION] == c1)
		cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) - 1] \
			[(int)cub->player_data->x / WALL_DIMENSION] = c2;
	else if (cub->matrice[(int)cub->player_data->y / WALL_DIMENSION] \
		[((int)cub->player_data->x / WALL_DIMENSION) + 1] == c1)
		cub->matrice[(int)cub->player_data->y / WALL_DIMENSION] \
			[((int)cub->player_data->x / WALL_DIMENSION) + 1] = c2;
	else if (cub->matrice[(int)cub->player_data->y / WALL_DIMENSION] \
		[((int)cub->player_data->x / WALL_DIMENSION) - 1] == c1)
		cub->matrice[(int)cub->player_data->y / WALL_DIMENSION] \
			[((int)cub->player_data->x / WALL_DIMENSION) - 1] = c2;
}

void	hor_intersec(t_cub3d_data *cub)
{
	calcs_horintercept(cub);
	if (cub->rays->is_rayfacingup)
	{
		cub->rays->ystep *= -1;
		cub->rays->xstep *= -1;
		cub->rays->hor_wallhity -= 0.01;
	}
	while (1)
	{
		if (protect_matrice(cub->rays->hor_wallhitx, \
			cub->rays->hor_wallhity, cub))
		{
			cub->rays->hor_cont = get_content(cub, cub->rays->hor_wallhitx, \
				cub->rays->hor_wallhity);
			if (cub->rays->is_rayfacingup)
				cub->rays->hor_wallhity += 0.01;
			cub->rays->foundhorzwallhit = 1;
			break ;
		}
		else
		{
			cub->rays->hor_wallhitx += cub->rays->xstep;
			cub->rays->hor_wallhity += cub->rays->ystep;
		}
	}
}

void	vert_intersec(t_cub3d_data *cub)
{
	calcs_vertintercept(cub);
	if (cub->rays->is_rayfacingleft)
	{
		cub->rays->xstep *= -1;
		cub->rays->ystep *= -1;
		cub->rays->vert_wallhitx -= 0.01;
	}	
	while (1)
	{
		if (protect_matrice(cub->rays->vert_wallhitx, \
			cub->rays->vert_wallhity, cub))
		{
			cub->rays->ver_cont = get_content(cub, cub->rays->vert_wallhitx, \
				cub->rays->vert_wallhity);
			if (cub->rays->is_rayfacingleft)
				cub->rays->vert_wallhitx += 0.01;
			cub->rays->foundverzwallhit = 1;
			break ;
		}
		else
		{
			cub->rays->vert_wallhitx += cub->rays->xstep;
			cub->rays->vert_wallhity += cub->rays->ystep;
		}
	}
}

void	found_door(t_cub3d_data *cub)
{
	if (cub->rays->map_cont == 'D')
		cub->rays->flag = 1;
}

void	ray_cast(t_cub3d_data *cub, double horz_dist, double vert_dist)
{
	raycasting_init(cub);
	hor_intersec(cub);
	vert_intersec(cub);
	if (cub->rays->foundhorzwallhit)
		horz_dist = distance_between_points(cub->player_data->x, cub->player_data->y, cub->rays->hor_wallhitx, cub->rays->hor_wallhity);
	if (cub->rays->foundverzwallhit)
		vert_dist = distance_between_points(cub->player_data->x, cub->player_data->y, cub->rays->vert_wallhitx, cub->rays->vert_wallhity);
	if (vert_dist < horz_dist)
	{
		cub->rays->wallhit_x = cub->rays->vert_wallhitx;
		cub->rays->wallhit_y = cub->rays->vert_wallhity;
		cub->rays->distance = vert_dist;
		cub->rays->map_cont = cub->rays->ver_cont;
		found_door(cub);
		cub->rays->hit_verti = 1;
	}
	else
	{
		cub->rays->wallhit_x = cub->rays->hor_wallhitx;
		cub->rays->wallhit_y = cub->rays->hor_wallhity;
		cub->rays->distance = horz_dist;
		cub->rays->map_cont = cub->rays->hor_cont;
		found_door(cub);
		cub->rays->hit_verti = 0;
	}
}
