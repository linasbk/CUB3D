/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhookutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/20 16:09:38 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_tur_direction(t_cub3d_data *cub)
{
	double	turn_dir;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		turn_dir = -1;
		cub->player_data->rot_angle += (turn_dir * ROT_SPEED);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		turn_dir = 1;
		cub->player_data->rot_angle += (turn_dir * ROT_SPEED);
	}	
}

void	walk_direction(t_cub3d_data *cub, int flag)
{
	double			walk_dir;
	double			px;
	double			py;
	double			mv_step;

	px = cub->player_data->x;
	py = cub->player_data->y;
	walk_dir = flag;
	mv_step = walk_dir * MV_SPEED;
	cub->player_data->x += cos(cub->player_data->rot_angle) * mv_step;
	cub->player_data->y += sin(cub->player_data->rot_angle) * mv_step;
	if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(cub->player_data->x / WALL_DIMENSION)] == '1' || \
	(cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(px / WALL_DIMENSION)] == '1' && cub->matrice[(int) \
	(py / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] \
	== '1') || cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(cub->player_data->x / WALL_DIMENSION)] == 'D')
	{
		cub->player_data->x = px;
		cub->player_data->y = py;
	}
}

void	side_direction(t_cub3d_data *cub, int flag)
{
	double			side_dir;
	double			px;
	double			py;
	double			mv_step;

	px = cub->player_data->x;
	py = cub->player_data->y;
	side_dir = flag;
	mv_step = side_dir * MV_SPEED;
	cub->player_data->x += cos(cub->player_data->rot_angle + \
	(M_PI / 2)) * mv_step;
	cub->player_data->y += sin(cub->player_data->rot_angle + \
	(M_PI / 2)) * mv_step;
	if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(cub->player_data->x / WALL_DIMENSION)] == '1' || \
	(cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(px / WALL_DIMENSION)] == '1' && cub->matrice[(int) \
	(py / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] \
	== '1') || cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)] \
	[(int)(cub->player_data->x / WALL_DIMENSION)] == 'D')
	{
		cub->player_data->x = px;
		cub->player_data->y = py;
	}
}

void	ft_door(t_cub3d_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_O))
		add_door(cub, 'D', 'd');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_C))
		add_door(cub, 'd', 'D');
}
