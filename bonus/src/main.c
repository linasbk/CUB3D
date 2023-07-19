/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/19 21:01:29 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

mlx_mousefunc	*ft_mouse(int x, int y, void *param)
{
	(void)param;
	printf ("%d\n%d\n", x, y);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d_data	*cub;

	cub = ft_calloc(1, sizeof(t_cub3d_data));
	if (map_parsing(cub, ac, av) == FAILURE)
		return (FAILURE);
	ft_mlx_init(cub);
	sky_floor(cub, 0, 0);
	read_color(cub);
	cub_img(cub);
	mlx_image_to_window(cub->mlx, cub->sky_floor, 0, 0);
	mlx_image_to_window(cub->mlx, cub->map_img, 0, 0);
	mlx_mouse_hook(cub->mlx, *(mlx_mousefunc *)ft_mouse, NULL);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	// mlx_texture_to_image(cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	return (SUCCESS);
}
