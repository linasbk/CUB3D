/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:34:42 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/25 14:55:25 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	sky_floor(t_cub3d_data *cub, int x, int y)
{
	cub->sky_floor = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->sky_floor)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub->sky_floor, x, y, get_color(cub->c_c->b, \
					cub->c_c->g, cub->c_c->r, 255));
			else
				mlx_put_pixel(cub->sky_floor, x, y, get_color(cub->c_f->b, \
					cub->c_f->g, cub->c_f->r, 255));
			y++;
		}
		x++;
	}
	free(cub->c_c);
	free(cub->c_f);
}

void	png_info(t_cub3d_data *cub, int num, mlx_texture_t *text)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	cub->walltexture[num] = ft_calloc(1, ((text->width * text->height * \
		+ 1) * sizeof(unsigned int)));
	while (j < (text->height * text->width))
	{
		cub->walltexture[num][j++] = get_color(text->pixels[i], \
			text->pixels[i + 1], text->pixels[i + 2], text->pixels[i + 3]);
		if (i < (text->height * text->width * 4) - 4)
			i += 4;
	}
}

void	load_png(mlx_texture_t **text, char *path)
{
	*text = mlx_load_png(path);
	if (!*text)
	{
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
}

void	read_color(t_cub3d_data *cub)
{
	int	i;

	load_png(&(cub->text[0]), cub->t_no);
	load_png(&(cub->text[1]), cub->t_so);
	load_png(&(cub->text[2]), cub->t_we);
	load_png(&(cub->text[3]), cub->t_ea);
	load_png(&(cub->text[4]), "images/black_door.png");
	load_png(&(cub->text[5]), "images/lights.png");
	load_png(&(cub->text[6]), "images/lights.png");
	load_png(&(cub->text[7]), "images/lights.png");
	load_png(&(cub->text[8]), "images/lights.png");
	load_png(&(cub->text[9]), "images/lights.png");
	load_png(&(cub->text[10]), "images/lights.png");
	load_png(&(cub->text[11]), "images/lights.png");
	load_png(&(cub->text[12]), "images/lights.png");
	load_png(&(cub->text[13]), "images/lights.png");
	load_png(&(cub->text[14]), "images/lights.png");
	load_png(&(cub->text[15]), "images/lights.png");
	load_png(&(cub->text[16]), "images/lights.png");
	load_png(&(cub->text[17]), "images/lights.png");
	load_png(&(cub->text[18]), "images/lights.png");
	load_png(&(cub->text[19]), "images/ferrari.png");
	load_png(&(cub->text[20]), "images/tree.png");
	load_png(&(cub->text[21]), "images/lights.png");
	load_png(&(cub->text[22]), "images/gta.png");
	i = -1;
	while (++i < 23)
		png_info(cub, i, cub->text[i]);
}
