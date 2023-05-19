#ifndef CUB3D_H
# define CUB3D_H

# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<limits.h>
# include"macros.h"

typedef struct s_map_color
{
	int	r;
	int	g;
	int	b;
}           t_map_color;

typedef struct cub3d_data
{
	char		**map;
	char		*t_no;
	char		*t_so;
	char		*t_we;
	char		*t_ea;
	int			t_index;
	t_map_color	*c_f;
	t_map_color	*c_c;
}           t_cub3d_data;

// UTILS
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *s);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
int		ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
//GET_NEXT_LINE && SPLIT
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
//PARSING
int	map_parsing(t_cub3d_data *cub, int ac, char **av);
//ERROR
int ft_error(char *s);
//INIT
int	init_data(t_cub3d_data *cub);
//VALID_COLOR
int		check_comma(t_cub3d_data *cube, char *line);
int		check_range(t_cub3d_data *cube, char *line);

#endif
