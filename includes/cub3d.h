/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:54:53 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/24 21:55:23 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "macros.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map_color
{
	int			r;
	int			g;
	int			b;
}				t_map_color;

typedef struct cub3d_data
{
	char		**map;
	char		*t_no;
	char		*t_so;
	char		*t_we;
	char		*t_ea;
	char		**matrice;
	int			t_index;
	int			m_index;
	char		*line;
	t_map_color	*c_f;
	t_map_color	*c_c;
}				t_cub3d_data;

// UTILS
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *s);
char			*ft_strdup(char *s1);
size_t			ft_strlen(char *s);
int				ft_strchr(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strtrim(char *s1, char *set);
int				ft_isspace(char str);
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
int				init_data(t_cub3d_data *cub);
//VALID_COLOR
t_map_color		*valide_color(t_cub3d_data *cub, char *str);
//VALID_MAP
int				check_map(t_cub3d_data *cub);
int				valid_char(char c);
#endif
