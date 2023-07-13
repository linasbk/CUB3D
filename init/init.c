/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/13 17:20:42 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	normalizeangle(double ray_angle)
{
	ray_angle = fmod(ray_angle, (2 * M_PI));
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	return (ray_angle);
}

void	ft_color(t_cub3d_data *cub)
{
	int	x = 0;
	int	y = 0;
	cub->texture = (uint32_t *)malloc(sizeof(uint32_t)*(uint32_t)TEXTUR_WIDTH * (uint32_t)TEXTUR_HEIGHT);
	while (x < TEXTUR_WIDTH)
	{
		y = 0;
		while (y < TEXTUR_HEIGHT)
		{
			if ((x % 4) && (y % 4))
				cub->texture[(TEXTUR_WIDTH * y) + x] = 0x0000FFFF;
			else
				cub->texture[(TEXTUR_WIDTH * y) + x] = 0x000000FF;
			y++;
		}
		x++;
	}
}

void	init_ray_data(t_cub3d_data *cub)
{
	cub->data_rays = ft_calloc(1, sizeof(t_ray_data));
	cub->data_rays->ray_angle = cub->player_data->rot_angle;
	cub->data_rays->is_rayfacingdown = 0;
	cub->data_rays->is_rayfacingright = 0;
	cub->data_rays->is_rayfacingup = 0;
	cub->data_rays->is_rayfacingleft = 0;
	// cub->data_rays->hor_wallhitX = 0;
	// cub->data_rays->hor_wallhitY = 0;
	// cub->data_rays->vert_wallhitX = 0;
	// cub->data_rays->vert_wallhitY = 0;
	// cub->data_rays->wasHitVertical = 0;
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
}

void	init_data_player(t_cub3d_data *cub)
{
	cub->player_data = ft_calloc(1, sizeof(t_data_player));
	if (cub->matrice[cub->player_y][cub->player_x])
	{
		cub->player_data->x = cub->player_x * WALL_DIMENSION + 10;
		cub->player_data->y = cub->player_y * WALL_DIMENSION + 10;
		if (cub->player_dir == 'E')
			cub->player_data->rot_angle = M_PI;
		if (cub->player_dir == 'N')
			cub->player_data->rot_angle = M_PI / 2;
		if (cub->player_dir == 'S')
			cub->player_data->rot_angle = (3 * M_PI) / 2;
		if (cub->player_dir == 'W')
			cub->player_data->rot_angle = 0;
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
