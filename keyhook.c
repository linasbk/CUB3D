/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:13:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/08 10:13:29 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


void	ft_hook(void *param)
{
	t_cub3d_data	*cub;
	int				y1;
	int				x1;

	cub = param;
	mlx_delete_image(cub->mlx, cub->map_img);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player_data->turn_direction = 1.0;
		if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
			cub->player_data->turn_direction = -1.0;
		cub->player_data->rotation_angle += (cub->player_data->turn_direction * cub->player_data->rotation_speed);
		cub->player_data->turn_direction = 0;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		cub->player_data->walk_direction = 1.0;
		if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
			cub->player_data->walk_direction = -1.0;
		x1 = cub->player_data->x;
		y1 = cub->player_data->y;
		cub->player_data->move_step = cub->player_data->walk_direction * cub->player_data->move_speed;
		cub->player_data->x += cos(cub->player_data->rotation_angle) * cub->player_data->move_step;
		cub->player_data->y += sin(cub->player_data->rotation_angle) * cub->player_data->move_step;
		if (cub->matrice[(int)cub->player_data->y / 20][(int)cub->player_data->x / 20] == '1')
		{
			cub->player_data->x = x1;
			cub->player_data->y = y1;
		}
		cub->player_data->walk_direction = 0;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) || mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		x1 = cub->player_data->x;
		y1 = cub->player_data->y;
		cub->player_data->side_direction = -1;
		if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
			cub->player_data->side_direction = 1;
		cub->player_data->move_step = cub->player_data->side_direction * cub->player_data->move_speed;
		cub->player_data->x += cos(cub->player_data->rotation_angle + (M_PI / 2)) * cub->player_data->move_step;
		cub->player_data->y += sin(cub->player_data->rotation_angle + (M_PI / 2)) * cub->player_data->move_step;
		if (cub->matrice[(int)cub->player_data->y / 20][(int)cub->player_data->x / 20] == '1')
		{
			cub->player_data->x = x1;
			cub->player_data->y = y1;
		}
		cub->player_data->side_direction = 0;
	}
	put_map(cub);
	mlx_image_to_window(cub->mlx, cub->map_img, 0, 0);

}
