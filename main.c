/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/12 10:45:48 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	sky_floor(t_cub3d_data *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	cub->sky_floor = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->sky_floor)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub->sky_floor, x, y, CYAN_MP);
			else
				mlx_put_pixel(cub->sky_floor, x, y, GREEN_MP);
			y++;
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	t_cub3d_data	*cub;

	cub = ft_calloc(1, sizeof(t_cub3d_data));
	if (map_parsing(cub, ac, av) == FAILURE)
		return (FAILURE);  
	ft_mlx_init(cub);
	sky_floor(cub);
	put_map(cub);
	mlx_image_to_window(cub->mlx, cub->sky_floor, 0, 0);
	mlx_image_to_window(cub->mlx, cub->map_img, 0, 0);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	return (SUCCESS);
}
