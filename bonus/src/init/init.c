/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/19 17:56:40 by nouahidi         ###   ########.fr       */
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
	cub->rays->ray_ang = cub->player_data->rot_angle;
	cub->rays->is_rayfacingdown = 0;
	cub->rays->is_rayfacingright = 0;
	cub->rays->is_rayfacingup = 0;
	cub->rays->is_rayfacingleft = 0;
}

void	puts_walls(int x, int y, t_cub3d_data *cub, int	flag)
{
	int	tmpx;
	int	tmpy;

	tmpx = x;
	tmpy = y;
	while (y < tmpy + cub->y_wall - 1)
	{
		x = tmpx;
		while (x < tmpx + cub->x_wall - 1)
		{
			if (flag == 1)
				mlx_put_pixel(cub->map_img, x++, y, GREEN_MP);
			else if (flag == 2)
				mlx_put_pixel(cub->map_img, x++, y, YELLOW_MP);
			else
				mlx_put_pixel(cub->map_img, x++, y, BLUE_MP);
		}
		y++;
	}
}

void	draw_fullmap(t_cub3d_data *cub)
{
	int			x;
	int			y;
	int			i;
	int			j;

	i = 0;
	j = 0;
	x = cub->beginx;
	y = cub->beginy;
	while (cub->matrice[j])
	{
		i = 0;
		x = cub->beginx;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i] == '1')
				puts_walls(x, y, cub, 1);
			else if (cub->matrice[j][i] == 'D')
				puts_walls(x, y, cub, 2);
			else
				puts_walls(x, y, cub, 0);
			i++;
			x = x + cub->x_wall;
			if (x > WIDTH - 200)
				break ;
		}
		y = y + cub->y_wall;
		j++;
		if (y > HEIGHT - 200)
			break ;
	}
}

void	puts_player(t_cub3d_data *cub)
{
	int x;
	int y;

	x = cub->player_data->mpx - 5;
	y = cub->player_data->mpy - 5;
	while (y < cub->player_data->mpy + 5)
	{
		x = cub->player_data->mpx - 5;
		while (x < cub->player_data->mpx + 5)
		{
			// puts("here");
			if (floor(distance(cub->player_data->mpx, cub->player_data->mpy, x, y)) < 5)
				mlx_put_pixel(cub->map_img, x, y, BLACK_MP);
			x++;
		}
		y++;
	}
}

void	setting_map(t_cub3d_data *cub)
{
	int			x;
	int			y;

	x = 200;
	y = 199;
	while (++y < 205)
	{
		x = 200;
		while (x < WIDTH_FULLMAP + 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	x = 200;
	y = 199;
	while (++y < HEIGHT_FULLMAP + 200)
	{
		x = 200;
		while (x < 205)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	x = 200;
	y = HEIGHT_FULLMAP + 199;
	while (++y < HEIGHT_FULLMAP + 205)
	{
		x = 200;
		while (x < WIDTH_FULLMAP + 200)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	x = WIDTH_FULLMAP + 200;
	y = 199;
	while (++y < HEIGHT_FULLMAP + 205)
	{
		x = WIDTH_FULLMAP + 200;
		while (x < WIDTH_FULLMAP + 205)
			mlx_put_pixel(cub->map_img, x++, y, BLACK_MP);
	}
	cub->x_wall = WIDTH_FULLMAP / cub->len_i;
	cub->y_wall = HEIGHT_FULLMAP / cub->len_j;
	cub->beginx = 205;
	cub->beginy = 205;
	draw_fullmap(cub);
	cub->player_data->mpx = ((cub->player_data->x / WALL_DIMENSION) * cub->x_wall) + 205;
	cub->player_data->mpy = ((cub->player_data->y / WALL_DIMENSION) * cub->y_wall) + 205;
	puts_player(cub);
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
	cub->openflag = 1;
	cub->doorflag = 0;
	cub->tm = 1;
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
