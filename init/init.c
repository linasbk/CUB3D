/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/31 21:09:46 by lsabik           ###   ########.fr       */
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
	cub->player = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->player)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
		// draw_circle(image->img, 100, 100, 50, 0xFFFFFFFF);
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
