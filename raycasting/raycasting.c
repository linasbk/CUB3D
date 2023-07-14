/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:59:00 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/14 20:19:01 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rayfacing_init(t_cub3d_data *cub)
{
	cub->data_rays->hor_wallhitX = WIDTH *20;
	cub->data_rays->hor_wallhitY = HEIGHT *20;
	cub->data_rays->vert_wallhitX = WIDTH *20;
	cub->data_rays->vert_wallhitY = HEIGHT *20;
	if (cub->data_rays->ray_angle > 0 && cub->data_rays->ray_angle < M_PI)
	{
		cub->data_rays->is_rayfacingup = 1;
		cub->data_rays->is_rayfacingdown = 0;
	}
	else
	{
		cub->data_rays->is_rayfacingdown = 1;
		cub->data_rays->is_rayfacingup = 0;
	}
	if (cub->data_rays->ray_angle < M_PI / 2 \
		|| cub->data_rays->ray_angle > (3 * M_PI) / 2)
	{
		cub->data_rays->is_rayfacingleft = 1;
		cub->data_rays->is_rayfacingright = 0;
	}
	else
	{
		cub->data_rays->is_rayfacingright = 1;
		cub->data_rays->is_rayfacingleft = 0;
	}
}

int	protect_matrice(double nextHorztouchX, double nextHorztouchY, t_cub3d_data *cub)
{
	int	x;
	int	y;

	x = floor(nextHorztouchX / WALL_DIMENSION);
	y = floor(nextHorztouchY / WALL_DIMENSION);
	if (x < 0 || x > cub->len_i || y < 0 || y > cub->len_j - 1)
		return (1);
	return(cub->matrice[y][x] == '1' || cub->matrice[y][x] == 'D');
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void    wall_intersecloop(t_cub3d_data *cub, double x, double y, int type)
{
	while (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		if (protect_matrice(x, y, cub))
		{
			if (type == VERTICAL)
			{
				
				if (cub->data_rays->is_rayfacingleft)
					x += 0.01;
				cub->data_rays->foundverzwallhit = 1;
				cub->data_rays->vert_wallhitX = x;
				cub->data_rays->vert_wallhitY = y;
			}
			else
			{
				if (cub->data_rays->is_rayfacingup)
					y += 0.01;
				cub->data_rays->foundhorzwallhit = 1;
				cub->data_rays->hor_wallhitX = x;
				cub->data_rays->hor_wallhitY = y;
			}
			break ;
		}
		else
		{
			x += cub->data_rays->xstep;
			y += cub->data_rays->ystep;
		}
	}
}

void    hor_intersec(t_cub3d_data *cub)
{
	double	nextHorztouchX; 
	double	nextHorztouchY;

	cub->data_rays->foundverzwallhit = 0;
	cub->data_rays->yintercept  = floor(cub->player_data->y / WALL_DIMENSION) * WALL_DIMENSION;
	if (cub->data_rays->is_rayfacingdown)
		cub->data_rays->yintercept  += WALL_DIMENSION;
	cub->data_rays->xintercept = cub->player_data->x + (cub->data_rays->yintercept  - cub->player_data->y) / tan(cub->data_rays->ray_angle);
	cub->data_rays->ystep = WALL_DIMENSION;
	cub->data_rays->xstep = WALL_DIMENSION / tan(cub->data_rays->ray_angle);
	if (cub->data_rays->is_rayfacingup)
		cub->data_rays->ystep *= -1;
	if (cub->data_rays->is_rayfacingleft && cub->data_rays->xstep > 0)
		cub->data_rays->xstep *= -1;
	if (cub->data_rays->is_rayfacingright && cub->data_rays->xstep < 0)
		cub->data_rays->xstep *= -1;
	nextHorztouchX = cub->data_rays->xintercept;
	nextHorztouchY = cub->data_rays->yintercept ;
	if (cub->data_rays->is_rayfacingup)
		nextHorztouchY -= 0.01;
	wall_intersecloop(cub, nextHorztouchX, nextHorztouchY, HORIZONTAL);
}

void    vert_intersec(t_cub3d_data *cub)
{
	double	nextvert_touchX;
	double	nextvert_touchY;

	cub->data_rays->foundverzwallhit = 0;
	cub->data_rays->xintercept = floor(cub->player_data->x / WALL_DIMENSION) * WALL_DIMENSION;
	if (cub->data_rays->is_rayfacingright)
		cub->data_rays->xintercept += WALL_DIMENSION;
	cub->data_rays->yintercept  = cub->player_data->y + (cub->data_rays->xintercept - cub->player_data->x) * tan(cub->data_rays->ray_angle);
	cub->data_rays->xstep = WALL_DIMENSION;
	if (cub->data_rays->is_rayfacingleft)
		cub->data_rays->xstep *= -1;
	cub->data_rays->ystep = WALL_DIMENSION * tan(cub->data_rays->ray_angle);
	if (cub->data_rays->is_rayfacingup && cub->data_rays->ystep > 0)
		cub->data_rays->ystep *= -1;
	if (cub->data_rays->is_rayfacingdown && cub->data_rays->ystep < 0)
		cub->data_rays->ystep *= -1;
	nextvert_touchX = cub->data_rays->xintercept;
	nextvert_touchY = cub->data_rays->yintercept ;
	if (cub->data_rays->is_rayfacingleft)
		nextvert_touchX -= 0.01;
	wall_intersecloop(cub, nextvert_touchX, nextvert_touchY, VERTICAL);
}


void	 ray_cast(t_cub3d_data *cub)
{	
	cub->data_rays->wallhitX = 0;
	cub->data_rays->wallhitY = 0;
	cub->data_rays->distance = 0;
	cub->data_rays->ray_angle = normalizeangle(cub->data_rays->ray_angle);
	rayfacing_init(cub);
	hor_intersec(cub);
	vert_intersec(cub);
	//calculate hor and ver distance and choose the smallest one
	double horzhitdistance = INT_MAX;
	double vertzhitdistance = INT_MAX;
	if (cub->data_rays->foundhorzwallhit)
		horzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, cub->data_rays->hor_wallhitX, cub->data_rays->hor_wallhitY);
	if (cub->data_rays->foundverzwallhit)
		vertzhitdistance = distance_between_points(cub->player_data->x, cub->player_data->y, cub->data_rays->vert_wallhitX, cub->data_rays->vert_wallhitY);
	if (vertzhitdistance < horzhitdistance)
	{
		cub->data_rays->wallhitX = cub->data_rays->vert_wallhitX;
		cub->data_rays->wallhitY = cub->data_rays->vert_wallhitY;
		cub->data_rays->distance = vertzhitdistance;
		cub->data_rays->wasHitVertical = 1;
	}
	else
	{
		cub->data_rays->wallhitX = cub->data_rays->hor_wallhitX;
		cub->data_rays->wallhitY = cub->data_rays->hor_wallhitY;
		cub->data_rays->distance = horzhitdistance;
		cub->data_rays->wasHitVertical = 0;
	}
	// drawline(cub->map_img, cub->player_data->x * MINIMAP_SCALE_FACTOR, cub->player_data->y* MINIMAP_SCALE_FACTOR, cub->data_rays->wallhitX* MINIMAP_SCALE_FACTOR, cub->data_rays->wallhitY* MINIMAP_SCALE_FACTOR, ORANGE_MP);
}

void	draw_rec(t_cub3d_data *cub, int x, int y, int width, int height)
{
	int i;
	int j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			if ((x + i < WIDTH && x + i > 0)  && (y + j < HEIGHT && y + j > 0) && cub->data_rays->wasHitVertical)
				mlx_put_pixel(cub->map_img, x + i, y + j, 0xCCCCCCFF);
			else
				mlx_put_pixel(cub->map_img, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

unsigned int	*get_dir(t_cub3d_data *cub)
{
	unsigned int	*wall_text = NULL;

	if (cub->data_rays->is_rayfacingup && !cub->data_rays->wasHitVertical)
		wall_text = cub->walltexture[0];
	else if (cub->data_rays->is_rayfacingdown && !cub->data_rays->wasHitVertical)
		wall_text = cub->walltexture[1];
	else if (cub->data_rays->is_rayfacingright && cub->data_rays->wasHitVertical)
		wall_text = cub->walltexture[2];
	else if (cub->data_rays->is_rayfacingleft && cub->data_rays->wasHitVertical)
		wall_text = cub->walltexture[3];
	return (wall_text);
}

void	renderwallproject(t_cub3d_data *cub, int i)
{
	int				textoffsetx;
	unsigned int	*text_wall;

	if (cub->data_rays->distance == 0)
		cub->data_rays->distance = 0.1;
	double corr_dis = cub->data_rays->distance * cos(cub->data_rays->ray_angle - cub->player_data->rot_angle);
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
	if (cub->data_rays->wasHitVertical)
		textoffsetx = (int)cub->data_rays->wallhitY % WALL_DIMENSION;
	else
		textoffsetx = (int)cub->data_rays->wallhitX % WALL_DIMENSION;
	text_wall = get_dir(cub);
	while (y < wallBottomPixel)
	{
		int distancefromtop = y + (wallstripheight / 2) - (HEIGHT / 2);
		int	textureoffsety = distancefromtop * ((float)TEXTUR_HEIGHT / wallstripheight);
		unsigned int texelcolor = text_wall[(TEXTUR_WIDTH * textureoffsety) + textoffsetx];
			mlx_put_pixel(cub->map_img, i, y, texelcolor);
		y++;
	}
}
