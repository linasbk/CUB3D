/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:58:30 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/24 21:39:07 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int	parseTopBottom_line(t_cub3d_data *cub)
{
	int i;

	i = 0;
	while (cub->matrice[0][i])
	{
		if (cub->matrice[0][i] == '1' || ft_isspace(cub->matrice[0][i]))
			i++;
		else
			return (ft_error("MAP ERROR"));
	}
	i = 0;
	while (cub->matrice[cub->m_index - 1][i])
	{
		if (cub->matrice[cub->m_index - 1][i] == '1'
			 || ft_isspace(cub->matrice[cub->m_index - 1][i]))
			i++;
		else
			return (ft_error("MAP ERROR"));
	}
	return (SUCCESS);
}

int	valid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	check_sides(t_cub3d_data *cub, int i, int j)
{
	if ((cub->matrice[i - 1][j] == ' ' || cub->matrice[i - 1][j] == '1') && (cub->matrice[i + 1][j] == ' ' || cub->matrice[i + 1][j] == '1')
		&& (cub->matrice[i][j - 1] == ' ' || cub->matrice[i][j - 1] == '1') && (cub->matrice[i][j + 1] == ' ' || cub->matrice[i][j + 1] == '1'))
		return (SUCCESS);
	return (ft_error("MAP ERROR"));
}

int	parse_mid(t_cub3d_data *cub, int i)
{
	int j;
	int ret;
	int len;

	j = 1;
	ret = 1;
	len = ft_strlen(cub->matrice[i]);
	while (cub->matrice[i][j] == ' ')
		j++;
	while (len > 0)
	{
		if (!(cub->matrice[i][len - 1] == ' '))
			break;
		len--;
	}
	if (cub->matrice[i][len - 1] != '1')
		ret = ft_error("MAP ERROR");
	while (j < len - 1)
	{
		if (valid_char(cub->matrice[i][j]) == FAILURE)
			ret = ft_error("MAP ERROR");
		else if (cub->matrice[i][j] == ' ')
			ret = check_sides(cub, i, j);
		if (ret == FAILURE)
			return (FAILURE);
		j++;
	}
	return (ret);
}

int	check_retLine(t_cub3d_data *cub)
{
	int i;
	int j;
	char *line;

	i = 0;
	j = 0;
	line = ft_strtrim(cub->line, "\n");
	while (line[i])
	{
		
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (FAILURE);
		else
			i++;
	}
	cub->matrice = ft_split(line, '\n');
	return (SUCCESS);
}

int check_map(t_cub3d_data *cub)
{
	int i;
	int ret;

	i = 1;
	ret = 1;
	if (check_retLine(cub) == FAILURE)
		return (ft_error("MAP ERROR"));
	while (i < cub->m_index - 1)
	{
		if (i == 0 || i == cub->m_index)
			ret = parseTopBottom_line(cub);
		else
			ret = parse_mid(cub, i);
		if (ret == FAILURE)
			return (FAILURE);
		i++;
	}
	return (ret);
}
