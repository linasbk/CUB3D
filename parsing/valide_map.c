/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:58:30 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/26 18:45:27 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parsetopbottom_line(t_cub3d_data *cub)
{
	int	i;

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

int	check_sides(t_cub3d_data *cub, int i, int j)
{
	if ((ft_isspace(cub->matrice[i - 1][j]) || cub->matrice[i - 1][j] == '1'
			|| cub->matrice[i - 1][j] == '\0') && (ft_isspace(cub->matrice[i
				+ 1][j]) || cub->matrice[i + 1][j] == '1' || cub->matrice[i
			+ 1][j] == '\0') && (ft_isspace(cub->matrice[i][j - 1])
			|| cub->matrice[i][j - 1] == '1' || cub->matrice[i][j - 1] == '\0')
		&& (ft_isspace(cub->matrice[i][j + 1]) || cub->matrice[i][j + 1] == '1'
			|| cub->matrice[i][j + 1] == '\0'))
		return (SUCCESS);
	return (ft_error("MAP ERROR"));
}

int	parse_mid(t_cub3d_data *cub, int i, int ret, int j)
{
	int	len;

	len = ft_strlen(cub->matrice[i]);
	while (len > 0)
	{
		if (!(cub->matrice[i][len - 1] == ' '))
			break ;
		len--;
	}
	if (cub->matrice[i][len - 1] != '1')
		ret = ft_error("MAP ERROR");
	while (j < len - 1)
	{
		if (valid_char(cub, cub->matrice[i][j]) == FAILURE)
			ret = ft_error("MAP ERROR");
		else if (cub->matrice[i][j] == ' ')
			ret = check_sides(cub, i, j);
		if (ret == FAILURE)
			return (FAILURE);
		j++;
	}
	return (ret);
}

int	check_retline(t_cub3d_data *cub)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!cub->line)
		return (FAILURE);
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

int	check_map(t_cub3d_data *cub)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	if (check_retline(cub) == FAILURE)
		return (ft_error("MAP ERROR"));
	while (i < cub->m_index - 1)
	{
		if (i == 0 || i == cub->m_index)
			ret = parsetopbottom_line(cub);
		else
			ret = parse_mid(cub, i, 1, 1);
		if (ret == FAILURE)
			return (FAILURE);
		i++;
	}
	return (ret);
}
