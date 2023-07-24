/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:13:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/24 19:16:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
pid_t		play_music(void)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
	{
		printf("Music process couldn't be forked :(");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args = ft_split("afplay sounds/gta.mp3", ' ');
		execv("/usr/bin/afplay", args);
	}
	return (pid);
}

void	add_sounds(t_cub3d_data *cub)
{
	pid_t	pid;

	(void)cub;
	pid = play_music();
	if (pid < 0)
		exit(EXIT_FAILURE);
}

void	ft_clear_window(t_cub3d_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(SUCCESS);
	}
	ft_memset(cub->map_img->pixels, 0,
		cub->map_img->width * cub->map_img->height * sizeof(int32_t));
	ft_memset(cub->full_map->pixels, 0, cub->full_map->width * \
		cub->full_map->height * sizeof(int32_t));
	ft_memset(cub->minimap->pixels, 0, cub->minimap->width * \
		cub->minimap->height * sizeof(int32_t));
	// ft_memset(cub->time->pixels, 0, cub->time->width * cub->time->height * sizeof(int32_t));
}

void	ft_hook(void *param)
{
	t_cub3d_data	*cub;

	cub = param;
	ft_clear_window(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		walk_direction(cub, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		walk_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		side_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		side_direction(cub, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_G))
		add_sounds(cub);
	ft_tur_direction(cub);
	ft_door(cub);
	cub_img(cub);
	display_current_time(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		setting_map(cub);
}
