/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:54:53 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/09 18:56:27 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "macros.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define WIDTH 2080
# define HEIGHT 1500
# define WALL_DIMENSION 20
// # define FOV_ANGLE 60 * (M_PI / 180)
typedef struct data_rays
{
	float	ray_angle;
	float	is_rayfacingdown;
	float	is_rayfacingup;
	float	is_rayfacingright;
	float	is_rayfacingleft;
}				t_ray_data;
typedef struct s_map_color
{
	int			r;
	int			g;
	int			b;
}				t_map_color;

typedef struct point {
	float	x;
	float	y;
	float	z;
	float	delta_x;
	float	delta_y;
}				t_point;

typedef struct player_movement
{
	char	position_1;
	float		x;
	float		y;
	int		i;
	int		j;
	float	radius;
	float	turn_direction;
	float	walk_direction;
	float	side_direction;
	float	rotation_angle;
	float	move_speed;
	float	move_step;
	float	rotation_speed;
	float	fov_angle;
	float	num_rays;
}				t_data_player;

typedef struct cub3d_data
{
	mlx_t			*mlx;
	float			angleIncrement;
	char			**map;
	char			*t_no;
	char			*t_so;
	char			*t_we;
	char			*t_ea;
	char			**matrice;
	int				t_index;
	int				m_index;
	char			*line;
	int				player_x;
	int				new_x;
	int				player_y;
	int				new_y;
	char			player_dir;
	int				len_i;
	int				len_j;
	t_ray_data		*data_rays;
	t_map_color		*c_f;
	t_map_color		*c_c;
	mlx_image_t		*player;
	mlx_image_t		*point;
	mlx_image_t		*minimap;
	mlx_image_t		*map_img;
	t_data_player	*player_data;

}					t_cub3d_data;

// UTILS
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *s);
char			*ft_strdup(char *s1);
size_t			ft_strlen(char *s);
int				ft_strchr(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, int len);
char			*ft_strtrim(char *s1, char *set);
int				ft_isspace(char str);
void			*ft_calloc(size_t count, size_t size);
//GET_NEXT_LINE && SPLIT && ATOI
char			*get_next_line(int fd);
char			**ft_split(char const *s, char c);
long			ft_atoi(char *str);
//PARSING
int				map_parsing(t_cub3d_data *cub, int ac, char **av);
int				cub_file(char *s);
//ERROR
int				ft_error(char *s);
//INIT
float			normalizeamgle(float angle);
int				init_data(t_cub3d_data *cub);
void			init_ray_data(t_cub3d_data *cub);
void			ft_mlx_init(t_cub3d_data *cub);
//VALID_COLOR
t_map_color		*valide_color(t_cub3d_data *cub, char *str);
//VALID_MAP
int				check_map(t_cub3d_data *cub);
int				valid_char(t_cub3d_data *cub, char c, int i, int j);
void			put_player(t_cub3d_data *cub);
void			ft_update(t_cub3d_data *cub);
void			put_map(t_cub3d_data *cub);
void			init_data_player(t_cub3d_data *cub);
void			ft_hook(void	*param);
void			cast_allrays(int color, t_cub3d_data *cub);
void	ray_cast(t_cub3d_data *cub, float colmnID);
//DRAW_LINE
void			draw_square(mlx_image_t *img, int x, int y, int size, int color);
// void			draw_line(void *mlx_ptr, float x, float y, int color, t_cub3d_data *cub, float ray_angle);
void			drawline(t_cub3d_data *cub, t_point *a, t_point *b, int color);
t_point			*get_points(int x, int y);
//HOOK
void	ft_hook(void *param);
#endif
