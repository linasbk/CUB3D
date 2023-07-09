/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/09 16:34:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	normalizeamgle(float ray_angle)
{
	ray_angle = fmod(ray_angle, (2 * M_PI));
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	return (ray_angle);
}

void	init_ray_data(t_cub3d_data *cub)
{
	cub->data_rays = ft_calloc(1, sizeof(t_ray_data));
	// cub->data_rays->ray_angle = normalizeamgle(cub->data_rays->ray_angle);
	// if (cub->data_rays->ray_angle > 0 && cub->data_rays->ray_angle < M_PI)
	// 	cub->data_rays->is_rayfacingdown = 1;
	// else
	// {
	// 	cub->data_rays->is_rayfacingdown = 0;
	// 	cub->data_rays->is_rayfacingup = 1;
	// }
	// if (cub->data_rays->ray_angle < 0.5 * M_PI \
	// 	|| cub->data_rays->ray_angle > 1.5 * M_PI)
	// 	cub->data_rays->is_rayfacingright = 1;
	// else
	// {
	// 	cub->data_rays->is_rayfacingright = 0;
	// 	cub->data_rays->is_rayfacingileft = 1;
	// }
}

void	ft_mlx_init(t_cub3d_data *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MyCub3D", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	init_data_player(cub);
	init_ray_data(cub);
	// cub->map_img = mlx_new_image(cub->mlx, cub->len_i * 20, cub->len_j * 20);
	// if (!cub->map_img)
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	exit(EXIT_FAILURE);
	// }
}

void	ft_player_dir(t_cub3d_data	*cub)
{
	if (cub->matrice[cub->player_y][cub->player_x])
	{
		cub->player_data->x = cub->player_x * 20 + 10;
		cub->player_data->y = cub->player_y * 20 + 10;
		if (cub->player_dir == 'E')
			cub->player_data->rotation_angle = 2 * M_PI;
		if (cub->player_dir == 'N')
			cub->player_data->rotation_angle = (3 * M_PI) / 2;
		if (cub->player_dir == 'S')
			cub->player_data->rotation_angle = M_PI / 2;
		if (cub->player_dir == 'W')
			cub->player_data->rotation_angle = M_PI;
	}
}

void	init_data_player(t_cub3d_data *cub)
{
	cub->player_data = ft_calloc(1, sizeof(t_data_player));
	cub->player_data->radius = 5.0;
	cub->player_data->move_speed = 3.0;
	cub->player_data->rotation_speed = 5.0 * (M_PI / 180);
	cub->player_data->turn_direction = 0;
	cub->player_data->walk_direction = 0;
	cub->player_data->side_direction = 0;
	cub->player_data->fov_angle = 1.04;
	ft_player_dir(cub);
	cub->player_data->num_rays = cub->len_i * 20;
}

int	init_data(t_cub3d_data *cub)
{
	cub->t_no = NULL;
	cub->t_so = NULL;
	cub->t_we = NULL;
	cub->t_ea = NULL;
	cub->c_c = NULL;
	cub->c_f = NULL;
	cub->line = NULL;
	cub->player_dir = '\0';
	cub->t_index = 0;
	cub->m_index = 0;
	return (0);
}
