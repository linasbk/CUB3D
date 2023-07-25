/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhookutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/25 15:56:03 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_tur_direction(t_cub3d_data *cub)
{
	double	turn_dir;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		turn_dir = -0.5;
		cub->player->rot_angle += (turn_dir * ROT_SPEED);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		turn_dir = 0.5;
		cub->player->rot_angle += (turn_dir * ROT_SPEED);
	}	
}

void	walk_direction(t_cub3d_data *cub, int flag)
{
	double			walk_dir;
	double			px;
	double			py;
	double			mv_step;

	px = cub->player->x;
	py = cub->player->y;
	walk_dir = flag;
	if (!cub->mode_fg)
	{
		mlx_delete_image(cub->mlx, cub->mode);
		cub->mode = mlx_texture_to_image(cub->mlx, cub->cj[cub->anim_flag]);
		cub->mode_fg = 0;
	}
	mv_step = walk_dir * MV_SPEED;
	if (cub->mode_fg)
		mv_step = walk_dir * MV_SPEED * 2;
	cub->player->x += cos(cub->player->rot_angle) * mv_step;
	cub->player->y += sin(cub->player->rot_angle) * mv_step;
	if (cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(cub->player->x / W_DM)] == '1' || \
	(cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(px / W_DM)] == '1' && cub->matrice[(int) \
	(py / W_DM)][(int)(cub->player->x / W_DM)] \
	== '1') || cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(cub->player->x / W_DM)] == 'D')
	{
		cub->player->x = px;
		cub->player->y = py;
	}
	if (!cub->mode_fg)
		mlx_image_to_window(cub->mlx, cub->mode, (WIDTH / 2) - \
		(cub->mode->width / 2), HEIGHT - cub->mode->height);
}

void	side_direction(t_cub3d_data *cub, int flag)
{
	double			side_dir;
	double			px;
	double			py;
	double			mv_step;

	px = cub->player->x;
	py = cub->player->y;
	side_dir = flag;
	mv_step = side_dir * MV_SPEED;
	cub->player->x += cos(cub->player->rot_angle + \
	(M_PI / 2)) * mv_step;
	cub->player->y += sin(cub->player->rot_angle + \
	(M_PI / 2)) * mv_step;
	if (cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(cub->player->x / W_DM)] == '1' || \
	(cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(px / W_DM)] == '1' && cub->matrice[(int) \
	(py / W_DM)][(int)(cub->player->x / W_DM)] \
	== '1') || cub->matrice[(int)(cub->player->y / W_DM)] \
	[(int)(cub->player->x / W_DM)] == 'D')
	{
		cub->player->x = px;
		cub->player->y = py;
	}
}

void	ft_door(t_cub3d_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_O))
		add_door(cub, 'D', 'd');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_C))
		add_door(cub, 'd', 'D');
}
