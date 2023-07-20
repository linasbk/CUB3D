/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:59:00 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/20 11:07:18 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
//DOOR 8 + 3 = 11/ 4 ENEM Y 9+ 3 = 12/ SPIKE 3 + 3 =6/ 4 CONTAINERS 7 + 3 =10/ TOTAL 10  REST 9 / 8/7/5/4/13

int get_content(t_cub3d_data *cub, int i, int j)
{
	int x;
	int y;
	
	x = floor(i / WALL_DIMENSION);
	y = floor(j / WALL_DIMENSION);
	if (x < 0 || x > cub->len_i || y < 0 || y > cub->len_j - 1)
		return (1);
	return ((int)cub->matrice[y][x]);
}

void	add_door(t_cub3d_data *cub, char c1, char c2)
{
	if (cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][(int)cub->player_data->x / WALL_DIMENSION] == c1)
		cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][(int)cub->player_data->x / WALL_DIMENSION] = c2;
	else if (cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) + 1][(int)cub->player_data->x / WALL_DIMENSION] == c1)
		cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) + 1][(int)cub->player_data->x / WALL_DIMENSION] = c2;
	else if (cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) - 1][(int)cub->player_data->x / WALL_DIMENSION] == c1)
		cub->matrice[((int)cub->player_data->y / WALL_DIMENSION) - 1][(int)cub->player_data->x / WALL_DIMENSION] = c2;
	else if (cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][((int)cub->player_data->x / WALL_DIMENSION) + 1] == c1)
		cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][((int)cub->player_data->x / WALL_DIMENSION) + 1] = c2;
	else if (cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][((int)cub->player_data->x / WALL_DIMENSION) - 1] == c1)
		cub->matrice[(int)cub->player_data->y / WALL_DIMENSION][((int)cub->player_data->x / WALL_DIMENSION) - 1] = c2;
}

void	hor_intersec(t_cub3d_data *cub)
{
	calcs_horintercept(cub);
	cub->rays->hor_wallhitx = cub->rays->xintercept;
	cub->rays->hor_wallhity = cub->rays->yintercept;
	if (cub->rays->is_rayfacingup)
	{
		cub->rays->ystep *= -1;
		cub->rays->xstep *= -1;
		cub->rays->hor_wallhity -= 0.01;
	}
	while (1)
	{
		if (protect_matrice(cub->rays->hor_wallhitx, \
			cub->rays->hor_wallhity, cub))
		{
			// if (protect_matrice(cub->rays->hor_wallhitx, \
			// 	cub->rays->hor_wallhity, cub) == 2)
			// 	cub->rays->flag = 1;
			cub->rays->hor_cont = get_content(cub, cub->rays->hor_wallhitx, cub->rays->hor_wallhity);
			if (cub->rays->is_rayfacingup)
				cub->rays->hor_wallhity += 0.01;
			cub->rays->foundhorzwallhit = 1;
			break ;
		}
		else
		{
			cub->rays->hor_wallhitx += cub->rays->xstep;
			cub->rays->hor_wallhity += cub->rays->ystep;
		}
	}
}

void    vert_intersec(t_cub3d_data *cub)
{
	calcs_vertintercept(cub);
	cub->rays->vert_wallhitx = cub->rays->xintercept;
	cub->rays->vert_wallhity = cub->rays->yintercept ;
	if (cub->rays->is_rayfacingleft)
	{
		cub->rays->xstep *= -1;
		cub->rays->ystep *= -1;
		cub->rays->vert_wallhitx -= 0.01;
	}	
	while (1)
	{
		if (protect_matrice(cub->rays->vert_wallhitx, \
			cub->rays->vert_wallhity, cub))
		{
			// if (protect_matrice(cub->rays->hor_wallhitx, \
			// 	cub->rays->hor_wallhity, cub) == 2)
			// 	cub->rays->flag = 1;
			cub->rays->ver_cont = get_content(cub, cub->rays->vert_wallhitx, cub->rays->vert_wallhity);
			if (cub->rays->is_rayfacingleft)
				cub->rays->vert_wallhitx += 0.01;
			cub->rays->foundverzwallhit = 1;
			break ;
		}
		else
		{
			cub->rays->vert_wallhitx += cub->rays->xstep;
			cub->rays->vert_wallhity += cub->rays->ystep;
		}
	}
}

void	ray_cast(t_cub3d_data *cub)
{	
	cub->rays->wallhit_x = 0;
	cub->rays->wallhit_y = 0;
	cub->rays->distance = 0;
	cub->rays->ray_ang = normalizeangle(cub->rays->ray_ang);
	raycasting_init(cub);
	hor_intersec(cub);
	vert_intersec(cub);
	double horzhitdistance = INT_MAX;
	double vertzhitdistance = INT_MAX;
	if (cub->rays->foundhorzwallhit)
		horzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, cub->rays->hor_wallhitx, cub->rays->hor_wallhity);
	if (cub->rays->foundverzwallhit)
		vertzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, cub->rays->vert_wallhitx, cub->rays->vert_wallhity);
	if (vertzhitdistance < horzhitdistance)
	{
		cub->rays->wallhit_x = cub->rays->vert_wallhitx;
		cub->rays->wallhit_y = cub->rays->vert_wallhity;
		cub->rays->distance = vertzhitdistance;
		cub->rays->map_cont = cub->rays->ver_cont;
		if (cub->rays->map_cont == 'D')
			cub->rays->flag = 1;
		cub->rays->hit_verti = 1;
	}
	else
	{
		cub->rays->wallhit_x = cub->rays->hor_wallhitx;
		cub->rays->wallhit_y = cub->rays->hor_wallhity;
		cub->rays->distance = horzhitdistance;
		cub->rays->map_cont = cub->rays->hor_cont;
		if (cub->rays->map_cont == 'D')
			cub->rays->flag = 1;
		cub->rays->hit_verti = 0;
	}
	// drawline(cub->map_img, cub->player_data->x * MINIMAP_SCALE, cub->player_data->y * MINIMAP_SCALE, cub->rays->wallhit_x * MINIMAP_SCALE, cub->rays->wallhit_y * MINIMAP_SCALE, RED_MP);
}

unsigned int	*get_dir(t_cub3d_data *cub)
{
	unsigned int	*wall_text;

	wall_text = NULL;
	if (cub->rays->is_rayfacingup && !cub->rays->hit_verti && cub->rays->flag == 1)
		wall_text = cub->walltexture[7];
	else if (cub->rays->is_rayfacingup && !cub->rays->hit_verti)
		wall_text = cub->walltexture[0];
	else if (cub->rays->is_rayfacingdown && !cub->rays->hit_verti && cub->rays->flag == 1)
		wall_text = cub->walltexture[7];
	else if (cub->rays->is_rayfacingdown && !cub->rays->hit_verti)
		wall_text = cub->walltexture[1];
	else if (cub->rays->is_rayfacingright && cub->rays->hit_verti && cub->rays->flag == 1)
		wall_text = cub->walltexture[7];
	else if (cub->rays->is_rayfacingright && cub->rays->hit_verti)
		wall_text = cub->walltexture[2];
	else if (cub->rays->is_rayfacingleft && cub->rays->hit_verti && cub->rays->flag == 1)
		wall_text = cub->walltexture[7];
	else if (cub->rays->is_rayfacingleft && cub->rays->hit_verti)
		wall_text = cub->walltexture[3];
	cub->rays->flag = 0;
	return (wall_text);
}

void	renderwallproject(t_cub3d_data *cub, int i)
{
	int				textoffsetx;
	unsigned int	*text_wall;

	if (cub->rays->distance == 0)
		cub->rays->distance = 0.1;
	double corr_dis = cub->rays->distance * cos(cub->rays->ray_ang - cub->player_data->rot_angle);
	double d_pr_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	double pr_wallheight = (WALL_DIMENSION / corr_dis) * d_pr_plane;
	int wallstripheight =(int) pr_wallheight;
    // render the wall from wallTopPixel to wallBottomPixel
	int wallTopPixel = (HEIGHT / 2) - (wallstripheight / 2);
	if (wallTopPixel < 0)
		wallTopPixel = 0;
	int wallBottomPixel = (HEIGHT / 2) + (wallstripheight / 2);
	if (wallBottomPixel > HEIGHT)
		wallBottomPixel = HEIGHT;
	int y = wallTopPixel;
	if (cub->rays->hit_verti)
		textoffsetx = (int)cub->rays->wallhit_y % WALL_DIMENSION;
	else
		textoffsetx = (int)cub->rays->wallhit_x % WALL_DIMENSION;
	// int tex_num = cub->rays->map_cont;
	text_wall = get_dir(cub);
	if (cub->rays->hit_verti)
        textoffsetx = (cub->rays->wallhit_y / WALL_DIMENSION - (int)cub->rays->wallhit_y / WALL_DIMENSION) * cub->text[0]->width;
    else
        textoffsetx = (cub->rays->wallhit_x / WALL_DIMENSION - (int)cub->rays->wallhit_x / WALL_DIMENSION) * cub->text[0]->width;
    text_wall = cub->walltexture[0];
    unsigned int texelcolor;
    while (y < wallBottomPixel)
    {
        int textureoffsety = (y - wallTopPixel) * ((double)cub->text[0]->height / wallstripheight);
            texelcolor = text_wall[(cub->text[0]->width * textureoffsety) + textoffsetx];
            if (i > 0 && i < WIDTH && y > 0 && y < HEIGHT)
            mlx_put_pixel(cub->map_img, i, y, texelcolor);
        y++;
    }
}
	// while (y < wallBottomPixel)
	// {
	// 	int distancefromtop = y + (wallstripheight / 2) - (HEIGHT / 2);
	// 	int	textureoffsety = distancefromtop * ((float)TEXTUR_HEIGHT / wallstripheight);
	// 	unsigned int texelcolor = text_wall[(TEXTUR_WIDTH * textureoffsety) + textoffsetx];
	// 		mlx_put_pixel(cub->map_img, i, y, texelcolor);
	// 	y++;
	// }
}
