/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/31 21:47:40 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void ft_hook(void* param)
{
	t_cub3d_data *cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP) && cub->matrice[(cub->player->instances[0].y - 1) / 10][(cub->player->instances[0].x) / 10] != '1')
		cub->player->instances[0].y -= 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) && cub->matrice[(cub->player->instances[0].y + 2) / 10][(cub->player->instances[0].x) / 10] != '1')
	{
		printf("x = %c\n",  cub->matrice[(cub->player->instances[0].y + 1) / 10][(cub->player->instances[0].x) / 10]);
		cub->player->instances[0].y += 1;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) && cub->matrice[(cub->player->instances[0].y) / 10][(cub->player->instances[0].x - 1) / 10] != '1')
		cub->player->instances[0].x -= 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) && cub->matrice[(cub->player->instances[0].y) / 10][(cub->player->instances[0].x + 1) / 10] != '1')
		cub->player->instances[0].x +=1;
}
void	draw_square(mlx_image_t *img, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == size - 1 || i == size - 1 || j == 0 || i == 0)
				mlx_put_pixel(img, x + i, y + j, 0x0000000);
			else
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
void	draw_player(mlx_image_t *img, int x, int y, int radius, int color)
{
	int i;
	int j;

	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			if ((i - radius) * (i - radius) + (j - radius) * (j - radius) <= radius * radius)
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_cub3d_data	*cub;

	cub = malloc(sizeof(t_cub3d_data));
	if (map_parsing(cub, ac, av) == FAILURE)
		return (FAILURE);
	ft_mlx_init(cub);
	cub->minimap = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	int x = 0;
	int y = 0;
	draw_player(cub->player, 0, 0, 4, 0xFF0000FF);
	while (cub->matrice[y])
	{
		x = 0;
		while (cub->matrice[y][x])
		{
			if (cub->matrice[y][x] == '1')
			{
				// printf("x = %d, y = %d\n", x, y); 
				draw_square(cub->minimap, x * 10, y * 10, 10, 0xFFFFFFFF);
				
			}
			if (cub->matrice[y][x] == 'N')
			{
				cub->player_x = x;
				cub->player_y = y;
				mlx_image_to_window(cub->mlx, cub->player, x * 10, y * 10);
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(cub->mlx, cub->minimap,0,0);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	return (EXIT_SUCCESS);
}
