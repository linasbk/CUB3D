/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:34:42 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/22 17:07:29 by lsabik           ###   ########.fr       */
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

	i = 0;
	while (i < 15)
		cub->text[i++] = malloc(sizeof(mlx_texture_t));
	load_png(&(cub->text[0]), cub->t_no);
	load_png(&(cub->text[1]), cub->t_so);
	load_png(&(cub->text[2]), cub->t_we);
	load_png(&(cub->text[3]), cub->t_ea);
	load_png(&(cub->text[4]), "images/DOOR.png");
	load_png(&(cub->text[5]), "images/kill0.png");
	load_png(&(cub->text[6]), "images/kill1.png");
	load_png(&(cub->text[7]), "images/kill2.png");
	load_png(&(cub->text[8]), "images/kill3.png");
	load_png(&(cub->text[9]), "images/kill4.png");
	load_png(&(cub->text[10]), "images/kill5.png");
	load_png(&(cub->text[11]), "images/kill6.png");
	load_png(&(cub->text[12]), "images/kill7.png");
	load_png(&(cub->text[13]), "images/kill8.png");
	load_png(&(cub->text[14]), "images/kill9.png");
	i = -1;
	while (++i < 15)
		png_info(cub, i, cub->text[i]);
}
