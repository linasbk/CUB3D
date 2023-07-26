/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/27 00:41:40 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalizeangle(double ray_ang)
{
	ray_ang = fmod(ray_ang, (2 * M_PI));
	if (ray_ang < 0)
		ray_ang = (2 * M_PI) + ray_ang;
	return (ray_ang);
}

void	init_ray_data(t_cub3d_data *cub)
{
	cub->rays = ft_calloc(1, sizeof(t_ray_data));
	cub->rays->ray_ang = cub->player->rot_angle;
	cub->rays->is_rayfacingdown = 0;
	cub->rays->is_rayfacingright = 0;
	cub->rays->is_rayfacingup = 0;
	cub->rays->is_rayfacingleft = 0;
	cub->d_pr_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
}

void	init_img(t_cub3d_data *cub)
{
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->full_map = mlx_new_image(cub->mlx, WIDTH_FULLMAP, HEIGHT_FULLMAP);
	cub->minimap = mlx_new_image(cub->mlx, MP_WIDTH, MP_HEIGHT);
	if (!cub->map_img || !cub->full_map || !cub->minimap)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_load_png(t_cub3d_data *cub)
{
	load_png(&(cub->cj[0]), "images/CJ1.png");
	load_png(&(cub->cj[1]), "images/CJ2.png");
	load_png(&(cub->cj[2]), "images/CJ3.png");
	load_png(&(cub->cj[3]), "images/CJ4.png");
	load_png(&(cub->cj[4]), "images/CJ5.png");
	load_png(&(cub->cj[5]), "images/CJ6.png");
	load_png(&(cub->cj[6]), "images/CJ7.png");
	load_png(&(cub->cj[7]), "images/CJ8.png");
	load_png(&(cub->cj[8]), "images/CJ9.png");
	load_png(&(cub->cj[9]), "images/CJ10.png");
	load_png(&(cub->cj[10]), "images/CJ11.png");
	load_png(&(cub->cj[11]), "images/CJ12.png");
	load_png(&(cub->cj[12]), "images/CJ13.png");
	load_png(&(cub->cj[13]), "images/CJ14.png");
	load_png(&(cub->cj[14]), "images/gtatime.png");
	load_png(&(cub->cj[15]), "images/wallpaper.png");
	load_png(&(cub->cj[16]), "images/lotoo.png");
}
