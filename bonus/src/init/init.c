/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/17 16:45:20 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_map(t_cub3d_data *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	cub->matrice = (char **)malloc((cub->len_j + 1) * sizeof(char **));
	while (cub->tmpmatrice[j])
	{
		i = 0;
		cub->matrice[j] = malloc(ft_strlen(cub->tmpmatrice[j]) + 1);
		while (cub->tmpmatrice[j][i])
		{
			cub->matrice[j][i] = cub->tmpmatrice[j][i];
			i++;
		}
		cub->matrice[j][i] = '\0';
		j++;
	}
	cub->matrice[j] = NULL;
}

void	copy_the_map(t_cub3d_data *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	cub->tmpmatrice = (char **)malloc((cub->len_j + 1) * sizeof(char **));
	while (j < cub->len_j)
	{
		i = 0;
		cub->tmpmatrice[j] = malloc(ft_strlen(cub->matrice[j]) + 1);
		while (cub->matrice[j][i])
		{
			cub->tmpmatrice[j][i] = cub->matrice[j][i];
			i++;
		}
		cub->tmpmatrice[j][i] = '\0';
		j++;
	}
	cub->tmpmatrice[j] = NULL;
}

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
	cub->rays->ray_ang = cub->player_data->rot_angle;
	cub->rays->is_rayfacingdown = 0;
	cub->rays->is_rayfacingright = 0;
	cub->rays->is_rayfacingup = 0;
	cub->rays->is_rayfacingleft = 0;
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
		cub->player_data->x = cub->player_x * WALL_DIMENSION;
		cub->player_data->y = cub->player_y * WALL_DIMENSION;
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
