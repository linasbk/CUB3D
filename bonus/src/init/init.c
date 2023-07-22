/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/22 16:48:19 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalizeangle(double ray_ang)
{
	ray_ang = fmod(ray_ang, (2 * M_PI));
	if (ray_ang < 0)
		ray_ang = (2 * M_PI) + ray_ang;
	return (ray_ang);
}

void	init_ray_data(t_cub3d_data *cub)
{
	cub->rays = ft_calloc(1, sizeof(t_ray_data));
	cub->rays->ray_ang = cub->player->rot_angle;
	cub->rays->is_rayfacingdown = 0;
	cub->rays->is_rayfacingright = 0;
	cub->rays->is_rayfacingup = 0;
	cub->rays->is_rayfacingleft = 0;
	cub->d_pr_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
}

void	ft_mlx_init(t_cub3d_data *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MyCub3D", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cub->vandal = mlx_load_png("images/barrel.png");
	cub->vandal_img = mlx_texture_to_image(cub->mlx, cub->vandal);
	init_data_player(cub);
	init_ray_data(cub);
	cub->openflag = 1;
	cub->doorflag = 0;
	cub->tm = 1;
	cub->mouse_x = WIDTH / 2;
	cub->mouse_y = HEIGHT / 2;
}

void	init_data_player(t_cub3d_data *cub)
{
	cub->player = ft_calloc(1, sizeof(t_data_player));
	if (cub->matrice[cub->player_y][cub->player_x])
	{
		cub->player->x = cub->player_x * W_DM + 32;
		cub->player->y = cub->player_y * W_DM + 32;
		if (cub->player_dir == 'E')
			cub->player->rot_angle = M_PI;
		if (cub->player_dir == 'N')
			cub->player->rot_angle = M_PI / 2;
		if (cub->player_dir == 'S')
			cub->player->rot_angle = (3 * M_PI) / 2;
		if (cub->player_dir == 'W')
			cub->player->rot_angle = 0;
	}
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
