/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:54:53 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/14 08:27:04 by nouahidi         ###   ########.fr       */
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

typedef struct data_rays
{
	double	ray_angle;
	double	is_rayfacingdown;
	double	is_rayfacingup;
	double	is_rayfacingright;
	double	is_rayfacingleft;
	double	yintercept;
	double	xintercept;
	double	ystep;
	double	xstep;
	int		foundhorzwallhit;
	double	hor_wallhitX;
	double	hor_wallhitY;
	int		foundverzwallhit;
	double	vert_wallhitX;
	double	vert_wallhitY;
	double	wasHitVertical;
	double	distance;
	double	wallhitX;
	double	wallhitY;
}				t_ray_data;

typedef struct s_map_color
{
	int			r;
	int			g;
	int			b;
}				t_map_color;

typedef struct player_movement
{
	double	x;
	double	y;
	int		i;
	int		j;
	double	rot_angle;
}				t_data_player;

typedef struct cub3d_data
{
	mlx_t			*mlx;
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
	int				player_y;
	char			player_dir;
	int				len_i;
	int				len_j;
	uint32_t		*texture;
	uint32_t		*list_color;
	mlx_texture_t	*text;
	t_ray_data		*data_rays;
	t_map_color		*c_f;
	t_map_color		*c_c;
	mlx_image_t		*sky_floor;
	mlx_image_t		*map_img;
	mlx_image_t		*mini_map;
	t_data_player	*player_data;
}					t_cub3d_data;

// UTILS
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *s);
char			*ft_strdup(char *s1);
int				ft_strlen(char *s);
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
double			normalizeangle(double angle);
int				init_data(t_cub3d_data *cub);
void			init_ray_data(t_cub3d_data *cub);
void			ft_mlx_init(t_cub3d_data *cub);
//VALID_COLOR
t_map_color		*valide_color(char *str);
//VALID_MAP
int				check_map(t_cub3d_data *cub);
int				valid_char(t_cub3d_data *cub, char c, int i, int j);
void			put_player(t_cub3d_data *cub);
void			ft_update(t_cub3d_data *cub);
void			put_map(t_cub3d_data *cub);
void			init_data_player(t_cub3d_data *cub);
void			ft_hook(void	*param);
void			cast_allrays(t_cub3d_data *cub);
void			ray_cast(t_cub3d_data *cub);
//DRAW_LINE
void			draw_square(mlx_image_t *img, int x, int y, int size, int color);
void	 		ray_cast(t_cub3d_data *cub);
void			drawline(void *mlx_ptr, int x1, int y1, int x2, int y2, int color);
//HOOK
void			ft_hook(void *param);
//render
void			renderwallproject(t_cub3d_data *cub, int i);
void			ft_color(t_cub3d_data *cub);
void			read_color(t_cub3d_data *cub);
void			put_minimap(t_cub3d_data *cub);
#endif
