/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/06/24 18:27:58 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int ft_pixel(int r, int g, int b, int a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	for (int i = 0; i < image->width; ++i)
// 	{
// 		for (int y = 0; y < image->height; ++y)
// 		{ 
// 			int color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(cub->player, i, y, color);
// 		}
// 	}
// }
void	ft_mlx_init(t_cub3d_data *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MyCub3D", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	init_data_player(cub);
}

void	init_data_player(t_cub3d_data *cub)
{
	int x = 0;
	int y = 0;

	cub->player_data = malloc(sizeof(t_data_player));
	cub->player_data->radius = 5.0;
	cub->player_data->move_speed = 2.0;
	cub->player_data->rotation_speed = 3.0 * (M_PI / 180);
	cub->player_data->turn_direction = 0;
	cub->player_data->walk_direction = 0;
	cub->player_data->side_direction = 0;
	cub->len_i = 0;
	while (cub->matrice[y])
	{
		x = 0;
		while (cub->matrice[y][x])
		{
			if (cub->matrice[y][x] == 'N' || cub->matrice[y][x] == 'S' ||
			cub->matrice[y][x] == 'E' || cub->matrice[y][x] == 'W')
			{
				cub->player_data->x = x * 20 + 10;
				cub->player_data->y = y * 20 + 10;
				cub->player_data->i = x;
				cub->player_data->j = y;
				cub->player_data->position_1 = cub->matrice[y][x];
				if (cub->player_data->position_1 == 'E')
					cub->player_data->rotation_angle = M_PI;
				if (cub->player_data->position_1 == 'N')
					cub->player_data->rotation_angle = M_PI / 2;
				if (cub->player_data->position_1 == 'S')
				cub->player_data->rotation_angle =  -M_PI / 2;
				if (cub->player_data->position_1 == 'W')
				cub->player_data->rotation_angle =  M_PI * 2;
			}
			x++;
		}
		if (cub->len_i < x)
			cub->len_i = x;
		y++;
	}
	cub->len_j = y;
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
	cub->t_index = 0;
	cub->m_index = 0;
	cub->player_x = 0;
	cub->player_y = 0;
	return (0);
}
