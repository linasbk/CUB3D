/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/20 13:49:46 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mouse(void *param)
{
	static int		xp;
	t_cub3d_data	*cub;
	static int		yp;
	int				turn_dir;

	cub = param;
	xp = cub->mouse_x;
	yp = cub->mouse_y;
	turn_dir = 0;
	mlx_get_mouse_pos(cub->mlx, &cub->mouse_x, &cub->mouse_y);
	if (cub->mouse_x > xp && cub->mouse_x >= 0 && cub->mouse_x <= WIDTH)
		turn_dir = 1.0;
	else if (cub->mouse_x <= xp && cub->mouse_x >= 0 && cub->mouse_x <= WIDTH)
		turn_dir = -1.0;
	cub->player_data->rot_angle += (turn_dir * ROT_SPEED);
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
	mlx_cursor_hook(cub->mlx, (void *)ft_mouse, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	// mlx_texture_to_image(cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	return (SUCCESS);
}
