/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:33 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/12 18:07:02 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_texture(t_cub3d_data *cub, char *line, int key)
{
	int	i;

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
				cub->c_f = valide_color(ft_strdup(&line[i]));
			else if (key == C_C && cub->c_c == NULL)
				cub->c_c = valide_color(ft_strdup(&line[i]));
			else
				return (ft_error(TEXTURE_ERROR));
			cub->t_index++;
			return (SUCCESS);
		}
	}
	return (ft_error(TEXTURE_ERROR));
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
		return (FAILURE);
}

int	check_lines(t_cub3d_data *cub, char *line)
{
	int	key;

	key = get_key(ft_strtrim(ft_strtrim(line, " "), "\t"));
	if (key >= T_NO && key <= C_C)
		return (check_texture(cub, ft_strtrim(ft_strtrim(line, " "), "\t"),
				key));
	else if (key == RET_LINE && cub->m_index != 0)
	{
		cub->line = ft_strjoin(cub->line, line);
		return (SUCCESS);
	}
	else if (key == RET_LINE && cub->m_index == 0)
		return (SUCCESS);
	else if (key == M_W && cub->t_index == 6)
	{
		cub->m_index++;
		cub->line = ft_strjoin(cub->line, line);
		return (SUCCESS);
	}
	return (ft_error(CONFIG_ERROR));
}

int	read_map(t_cub3d_data *cub, char *av, int fd)
{
	char	*line;
	int		i;

	i = 0;
	(void)av;
	line = get_next_line(fd);
	cub->len_i = ft_strlen(line) - 1;
	while (line)
	{
		if (check_lines(cub, line) == -1)
			return (FAILURE);
		free(line);
		line = get_next_line(fd);
		if (line && ft_strlen(line) > cub->len_i)
			cub->len_i = ft_strlen(line) - 1;
	}
	free(line);
	close(fd);
	if (check_map(cub) == FAILURE)
		return (ft_error("MAP ERROR"));
	return (SUCCESS);
}

int	map_parsing(t_cub3d_data *cub, int ac, char **av)
{
	int	fd;

	if (ac != 2 || (cub_file(av[1]) == -1))
		return (ft_error(INVALIDE_ARGS));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_error(NON_EXIT_FILE));
	init_data(cub);
	if (read_map(cub, av[1], fd) == -1)
		return (FAILURE);
	return (SUCCESS);
}
