/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:08:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/20 18:59:07 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	index_dir(t_cub3d_data *cub)
{
	int	i;

	i = 0;
	if (cub->rays->is_rayfacingup && !cub->rays->hit_verti \
		&& cub->rays->flag == 1)
		i = 5;
	else if (cub->rays->is_rayfacingup && !cub->rays->hit_verti)
		i = 0;
	else if (cub->rays->is_rayfacingdown && !cub->rays->hit_verti \
		&& cub->rays->flag == 1)
		i = 5;
	else if (cub->rays->is_rayfacingright && cub->rays->hit_verti \
		&& cub->rays->flag == 1)
		i = 5;
	else if (cub->rays->is_rayfacingleft && cub->rays->hit_verti && \
		cub->rays->flag == 1)
		i = 5;
	else if (cub->rays->is_rayfacingdown && !cub->rays->hit_verti)
		i = 1;
	else if (cub->rays->is_rayfacingright && cub->rays->hit_verti)
		i = 2;
	else if (cub->rays->is_rayfacingleft && cub->rays->hit_verti)
		i = 3;
	cub->rays->flag = 0;
	return (i);
}

void	caluc_offest_x(t_cub3d_data *cub, int f)
{
	if (cub->rays->hit_verti)
		cub->text_offsetx = (cub->rays->wallhit_y / WALL_DIMENSION \
		- (int)cub->rays->wallhit_y / WALL_DIMENSION) * cub->text[f]->width;
	else
		cub->text_offsetx = (cub->rays->wallhit_x / WALL_DIMENSION - \
		(int)cub->rays->wallhit_x / WALL_DIMENSION) * cub->text[f]->width;
}

double	fix_fishbowl(t_cub3d_data *cub)
{
	if (cub->rays->distance == 0)
		cub->rays->distance = 0.1;
	return (cub->rays->distance *= cos(cub->rays->ray_ang - \
		cub->player_data->rot_angle));
}

void	renderwallproject(t_cub3d_data *cub, int x, int text_index)
{
	int				y;
	unsigned int	*text_wall;
	double			corr_dis;
	unsigned int	texelcolor;

	corr_dis = fix_fishbowl(cub);
	cub->d_pr_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	cub->wallstripheight =(int)((WALL_DIMENSION / corr_dis) * cub->d_pr_plane);
	cub->wallTopPixel = (HEIGHT / 2) - (cub->wallstripheight / 2);
	cub->wallBottomPixel = (HEIGHT / 2) + (cub->wallstripheight / 2);
	text_wall = cub->walltexture[text_index];
	caluc_offest_x(cub, text_index);
	y = cub->wallTopPixel;
	while (y < cub->wallBottomPixel)
	{
		if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		{
			cub->text_offsety = (y - cub->wallTopPixel) * \
				((double)cub->text[text_index]->height / cub->wallstripheight);
			texelcolor = text_wall[(cub->text[text_index]->width \
				* cub->text_offsety) + cub->text_offsetx];
				mlx_put_pixel(cub->map_img, x, y, texelcolor);
		}
		y++;
	}
}


// void	caluc_offest_x(t_cub3d_data *cub)
// {
// 	if (cub->rays->hit_verti)
// 		cub->text_offsetx = (cub->rays->wallhit_y / WALL_DIMENSION - (int)cub->rays->wallhit_y \
// 			/ WALL_DIMENSION) * cub->text[index_dir(cub)]->width;
// 	else
// 		cub->text_offsetx = (cub->rays->wallhit_x / WALL_DIMENSION - (int)cub->rays->wallhit_x \
// 			/ WALL_DIMENSION) * cub->text[index_dir(cub)]->width;
// }

// double	fix_fishbowl(t_cub3d_data *cub)
// {
// 	if (cub->rays->distance == 0)
// 		cub->rays->distance = 0.1;
// 	return (cub->rays->distance *= cos(cub->rays->ray_ang - cub->player_data->rot_angle));
// }

// void	renderwallproject(t_cub3d_data *cub, int x)
// {
// 	int 			y;
// 	unsigned int	*text_wall;
// 	double			corr_dis;
// 	unsigned int	texelcolor;
	
// 	corr_dis = fix_fishbowl(cub);
// 	cub->d_pr_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
// 	cub->wallstripheight =(int) ((WALL_DIMENSION / corr_dis) * cub->d_pr_plane);
// 	cub->wallTopPixel = (HEIGHT / 2) - (cub->wallstripheight / 2);
// 	cub->wallBottomPixel = (HEIGHT / 2) + (cub->wallstripheight / 2);
// 	text_wall = cub->walltexture[index_dir(cub)];
// 	caluc_offest_x(cub);
// 	y = cub->wallTopPixel;
// 	while (y < cub->wallBottomPixel)
// 	{
// 			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
// 			{
// 				cub->text_offsety = (y - cub->wallTopPixel) * \
// 					((double)cub->text[index_dir(cub)]->height / cub->wallstripheight);
// 				texelcolor = text_wall[(cub->text[index_dir(cub)]->width \
// 					* cub->text_offsety) + cub->text_offsetx];
// 					mlx_put_pixel(cub->map_img, x, y, texelcolor);
// 			}
// 		y++;
// 	}
// }

