/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:13:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/23 11:50:17 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_hook(void *param)
{
	t_cub3d_data	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(SUCCESS);
	}
	ft_memset(cub->map_img->pixels, 0,
		cub->map_img->width * cub->map_img->height * sizeof(int32_t));
	ft_memset(cub->full_map->pixels, 0, cub->full_map->width * cub->full_map->height * sizeof(int32_t));
	ft_memset(cub->minimap->pixels, 0, cub->minimap->width * cub->minimap->height * sizeof(int32_t));
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		walk_direction(cub, 1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		walk_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		side_direction(cub, -1);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		side_direction(cub, 1);
	ft_tur_direction(cub);
	ft_door(cub);
	cub_img(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		setting_map(cub);
}
