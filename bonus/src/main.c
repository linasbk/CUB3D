/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/22 17:06:21 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mouse(void *param)
{
	t_cub3d_data	*cub;
	int				x;
	double			turn_dir;

	cub = param;
	x = WIDTH / 2;
	turn_dir = 0;
	mlx_get_mouse_pos(cub->mlx, &cub->mouse_x, &cub->mouse_y);
	cub->player->rot_angle += (cub->mouse_x - 500) / 500.0 * SENSE;
	mlx_set_mouse_pos(cub->mlx, 500, 500);
}

void	free_all(t_cub3d_data *cub)
{
	free(cub->t_no);
	free(cub->t_so);
	free(cub->t_ea);
	free(cub->t_we);
	free(cub->player);
	free(cub->rays);
	while (*cub->matrice)
	{
		free(*cub->matrice);
		cub->matrice++;
	}
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
	mlx_image_to_window(cub->mlx, cub->vandal_img, (WIDTH / 2) - (cub->vandal_img->width / 2), HEIGHT - cub->vandal_img->height);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(cub->mlx, (void *)ft_mouse, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	free_all(cub);
	return (SUCCESS);
}
