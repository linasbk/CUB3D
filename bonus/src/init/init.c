/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/17 13:05:47 by nouahidi         ###   ########.fr       */
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

void	puts_walls(int x, int y, t_cub3d_data *cub)
{
	int	tmpx;
	int	tmpy;

	tmpx = x;
	tmpy = y;
	while (y < tmpy + 20)
	{
		x = tmpx;
		while (x < tmpx + 20)
			mlx_put_pixel(cub->map_img, x++, y, get_color(0, 255, 0, 10));
		y++;
	}
}

void	draw_fullmap(t_cub3d_data *cub)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	j = -1;
	x = cub->beginx;
	y = cub->beginy;
	while (cub->matrice[++j])
	{
		i = 0;
		x = cub->beginx;
		while (cub->matrice[j][i])
		{
			if (cub->matrice[j][i++] == '1')
				puts_walls(x, y, cub);
			x = x + 20;
			if (x > WIDTH)
				break ;
		}
		y = y + 20;
		if (y >= HEIGHT - 200)
			break ;
	}
}

void	puts_player(t_cub3d_data *cub)
{
	int x;
	int y;

	x = cub->player_data->mpx - 5;
	y = cub->player_data->mpx - 5;
	while (y < cub->player_data->mpx + 5)
	{
		x = cub->player_data->mpx - 5;
		while (x < cub->player_data->mpx + 5)
		{
			// if (distance(cub->player_data->mpx, cub->player_data->mpy, x, y) <= 5){
			// puts("here");
				mlx_put_pixel(cub->map_img, x, y, BLACK_MP);
			x++;
		}
		y++;
	}
}
void	setting_map(t_cub3d_data *cub)
{
	int	x;
	int	y;
	static int	flage;

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
	cub->lenx_fullmap = cub->len_i * 20;
	cub->leny_fullmap = cub->len_j * 20;
	cub->beginx = ((WIDTH_FULLMAP - cub->lenx_fullmap) / 2) + 200;
	cub->beginy = ((HEIGHT_FULLMAP - cub->leny_fullmap) / 2 + 200);
	if (cub->len_j * 20 > HEIGHT_FULLMAP)
		cub->beginy =  205;
	if (!flage)
	{
		printf("---->%f", floor(cub->player_data->x / WALL_DIMENSION));
		cub->player_data->mpx = (floor(cub->player_data->x / WALL_DIMENSION) * 20);
		cub->player_data->mpy = (floor(cub->player_data->y / WALL_DIMENSION) * 20);
		puts_player(cub);
	}
	draw_fullmap(cub);
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
