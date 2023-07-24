/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:32 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/24 20:09:36 by lsabik           ###   ########.fr       */
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

void	ft_mlx_init(t_cub3d_data *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MyCub3D", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cub->map_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->full_map = mlx_new_image(cub->mlx, WIDTH_FULLMAP, HEIGHT_FULLMAP);
	cub->minimap = mlx_new_image(cub->mlx, MP_WIDTH, MP_HEIGHT);
	if (!cub->map_img)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	cub->walk_flag = 5;
	cub->anim_flag = 5;
	load_png(&(cub->cj[0]), "images/gtatime.png");
	load_png(&(cub->cj[1]), IMG_MODE);
	load_png(&(cub->cj[2]), IMG_MODE);
	load_png(&(cub->cj[3]), IMG_MODE);
	load_png(&(cub->cj[4]), IMG_MODE);
	load_png(&(cub->cj[5]), "images/CJ1.png");
	load_png(&(cub->cj[6]), "images/CJ2.png");
	load_png(&(cub->cj[7]), "images/CJ3.png");
	load_png(&(cub->cj[8]), "images/CJ4.png");
	load_png(&(cub->cj[9]), "images/CJ5.png");
	load_png(&(cub->cj[10]), "images/CJ6.png");
	load_png(&(cub->cj[11]), "images/CJ7.png");
	load_png(&(cub->cj[12]), "images/CJ8.png");
	load_png(&(cub->cj[13]), "images/CJ9.png");
	load_png(&(cub->cj[14]), "images/CJ10.png");
	load_png(&(cub->cj[15]), "images/CJ11.png");
	load_png(&(cub->cj[16]), "images/CJ12.png");
	load_png(&(cub->cj[17]), "images/CJ13.png");
	load_png(&(cub->cj[18]), "images/CJ14.png");
	cub->mode = mlx_texture_to_image(cub->mlx, cub->cj[cub->anim_flag]);
	cub->screen_img = mlx_texture_to_image(cub->mlx, cub->cj[0]);
	init_data_player(cub);
	init_ray_data(cub);
	cub->openflag = 1;
	cub->doorflag = 0;
	cub->tm = 1;
	cub->mouse_x = WIDTH / 2;
	cub->mouse_y = HEIGHT / 2;
}

void	init_data_player(t_cub3d_data *cub)
{
	cub->player = ft_calloc(1, sizeof(t_data_player));
	if (cub->matrice[cub->player_y][cub->player_x])
	{
		cub->player->x = cub->player_x * W_DM + 32;
		cub->player->y = cub->player_y * W_DM + 32;
		if (cub->player_dir == 'E')
			cub->player->rot_angle = M_PI;
		if (cub->player_dir == 'N')
			cub->player->rot_angle = M_PI / 2;
		if (cub->player_dir == 'S')
			cub->player->rot_angle = (3 * M_PI) / 2;
		if (cub->player_dir == 'W')
			cub->player->rot_angle = 0;
	}
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
	cub->player_dir = '\0';
	cub->t_index = 0;
	cub->m_index = 0;
	return (0);
}
