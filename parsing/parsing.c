/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:33 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/19 21:48:28 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"
#include"../includes/macros.h"
int	cub_file(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ".cub";
	
	while (s && s[i])
	{
		if (s && s[i] == str[0] && ft_strcmp(s + i, str) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (FAILURE);
}

t_map_color	*valide_color(t_cub3d_data *cub, char *str)
{
	t_map_color	*color;

	if (check_comma(cub, str) == FAILURE)
		exit(EXIT_FAILURE);
	color = check_range(cub, str);
	return (color);
}

int	check_texture(t_cub3d_data *cub, char *line, int key)
{
	int	i;
	int	direc;

	i = 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '\n' || line[i] == '\0')
			return (ft_error(TEXTURE_ERROR));
		else
		{
			if (key == T_NO && cub->t_no == NULL)
				cub->t_no = ft_strdup(&line[i]);
			else if (key == T_SO && cub->t_so == NULL)
				cub->t_so = ft_strdup(&line[i]);
			else if (key == T_WE && cub->t_we == NULL)
				cub->t_we = ft_strdup(&line[i]);
			else if (key == T_EA && cub->t_ea == NULL)
				cub->t_ea = ft_strdup(&line[i]);
			else if (key == C_F && cub->c_f == NULL)
				cub->c_f = valide_color(cub, ft_strdup(&line[i]));
			else if (key == C_C && cub->c_c == NULL)
				cub->c_c = valide_color(cub, ft_strdup(&line[i]));
			else
				return (ft_error(TEXTURE_ERROR));
			cub->t_index++;
			return (EXIT_SUCCESS);
		}
	}
	return (FAILURE);
}

int	get_key(char *line)
{	
	if (!line || !line[0])
		return (-1);
	if (line[0] == 'N' && line[1] == 'O')
		return (T_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (T_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (T_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (T_EA);
	else if (line[0] == 'F')
		return (C_F);
	else if (line[0] == 'C')
		return (C_C);
	else if (line[0] == '1')
		return (M_W);
	else if (line[0] == '\n')
		return (RET_LINE);
	else
		return (ft_error(CONFIG_ERROR));
}

int	check_lines(t_cub3d_data *cub, char *line)
{
	int	key;

	while (line[0] == ' ' || line[0] == '\t')
		line++;
	key = get_key(ft_strtrim(line, " "));
	if (key >= T_NO && key <= C_C)
		return (check_texture(cub, ft_strtrim(line, " "), key));
	else if (key == RET_LINE)
		return (SUCCESS);
	else if (key == M_W && cub->t_index == 6)
		return (SUCCESS);
		// return (check_map(cub));
	return (ft_error(CONFIG_ERROR));
}

int	read_map(t_cub3d_data *cub, char *av, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line > 0)
	{
		if (check_lines(cub, line) == -1)
			return (FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (EXIT_SUCCESS);
}

int	map_parsing(t_cub3d_data *cub, int ac, char **av)
{
	int	fd;

	if (ac != 2 || (cub_file(av[1]) == -1))
		return(ft_error(INVALIDE_ARGS));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(ft_error(NON_EXIT_FILE));
	init_data(cub);
	if (read_map(cub, av[1], fd) == -1)
		return (FAILURE);
	return (EXIT_SUCCESS);
}
