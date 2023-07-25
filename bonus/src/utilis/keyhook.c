/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:13:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/25 15:50:41 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
pid_t		play_music(t_cub3d_data *cub, char *path)
{
	char	**args;
	pid_t	pid;

	pid = fork(); 
	if (pid < 0)
	{
		printf("Music process couldn't be forked :(");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args = ft_split(path, ' ');
		execv("/usr/bin/afplay", args);
	}
	return (pid);
}

void	add_sounds(t_cub3d_data *cub, int sound)
{
	pid_t	pid;

	pid = 0;
	if (sound == G)
		pid = play_music(cub, "afplay sounds/gta.mp3");
	else if (sound == K)
		pid = play_music(cub, "afplay sounds/Klaxon.wav");
	else if (sound == C)
		cub->pid = play_music(cub, "afplay sounds/intro.mp3");
	if (pid < 0 || cub->pid < 0)
		exit(EXIT_FAILURE);
}

void	ft_clear_window(t_cub3d_data *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		kill(cub->pid, SIGKILL);
		mlx_close_window(cub->mlx);
		exit(SUCCESS);
	}
	ft_memset(cub->map_img->pixels, 0,
		cub->map_img->width * cub->map_img->height * sizeof(int32_t));
	ft_memset(cub->full_map->pixels, 0, cub->full_map->width * \
		cub->full_map->height * sizeof(int32_t));
	ft_memset(cub->minimap->pixels, 0, cub->minimap->width * \
		cub->minimap->height * sizeof(int32_t));
}

int	ft_change_mode(t_cub3d_data *cub, char c1, char c2)
{
	if (cub->matrice[((int)cub->player->y / W_DM) + 1] \
		[(int)cub->player->x / W_DM] == c1)
		cub->matrice[((int)cub->player->y / W_DM) + 1] \
			[(int)cub->player->x / W_DM] = c2;
	else if (cub->matrice[((int)cub->player->y / W_DM) - 1] \
		[(int)cub->player->x / W_DM] == c1)
		cub->matrice[((int)cub->player->y / W_DM) - 1] \
			[(int)cub->player->x / W_DM] = c2;
	else if (cub->matrice[(int)cub->player->y / W_DM] \
		[((int)cub->player->x / W_DM) + 1] == c1)
		cub->matrice[(int)cub->player->y / W_DM] \
			[((int)cub->player->x / W_DM) + 1] = c2;
	else if (cub->matrice[(int)cub->player->y / W_DM] \
		[((int)cub->player->x / W_DM) - 1] == c1)
		cub->matrice[(int)cub->player->y / W_DM] \
			[((int)cub->player->x / W_DM) - 1] = c2;
	else
		return (0);
	return (1);
}

void	ft_drive(t_cub3d_data *cub)
{
	if (!cub->mode_fg)
	{
		if (ft_change_mode(cub, 'y', '0'))
		{
			mlx_delete_image(cub->mlx, cub->mode);
			cub->mode = mlx_texture_to_image(cub->mlx, cub->cj[2]);
			cub->mode_fg = 1;
			mlx_image_to_window(cub->mlx, cub->mode, 0, 0);
			mlx_image_to_window(cub->mlx, cub->minimap, 0, HEIGHT - MP_HEIGHT);
		}
	}
	else if (cub->mode_fg)
	{
		if (ft_change_mode(cub, '0', 'y'))
		{
			mlx_delete_image(cub->mlx, cub->mode);
			cub->mode = mlx_texture_to_image(cub->mlx, cub->cj[cub->anim_flag]);
			cub->mode_fg = 0;
			mlx_image_to_window(cub->mlx, cub->mode, (WIDTH / 2) - \
		(cub->mode->width / 2), HEIGHT - cub->mode->height);
		}
	}
}

void	ft_hook(void *param)
{
	t_cub3d_data	*cub;
	static int		time;

	cub = param;
	ft_clear_window(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_F))
		ft_drive(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		walk_direction(cub, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		walk_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		side_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		side_direction(cub, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_G))
		add_sounds(cub, G);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_K) && cub->mode_fg)
		add_sounds(cub, K);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
	{
		kill(cub->pid, SIGKILL);
		mlx_delete_image(cub->mlx, cub->intro);
	}
	if (time == 100)
	{
		ft_memset(cub->time->pixels, 0, cub->time->width * \
		cub->time->height * sizeof(int32_t));
		time = 0;
		display_current_time(cub);
	}
	time++;
	ft_tur_direction(cub);
	ft_door(cub);
	cub_img(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		setting_map(cub);
}
