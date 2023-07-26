/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:58:30 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/25 19:00:47 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsetopbottom_line(t_cub3d_data *cub)
{
	int	i;

	i = 0;
	while (cub->matrice[0][i])
	{
		if (cub->matrice[0][i] == '1' || cub->matrice[0][i] == ' ')
			i++;
		else
			return (FAILURE);
	}
	i = 0;
	while (cub->matrice[cub->m_index - 1][i])
	{
		if (cub->matrice[cub->m_index - 1][i] == '1' || cub->matrice[cub->m_index - 1][i] == ' ')
			i++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
int	check_sides(t_cub3d_data *cub, int i, int j)
{
	if (check_space(cub->matrice[i - 1][j]) == 1)
		return (FAILURE);
	if (check_space(cub->matrice[i + 1][j]) == 1)
		return (FAILURE);
	if (check_space(cub->matrice[i][j - 1]) == 1)
		return (FAILURE);
	if (check_space(cub->matrice[i][j + 1]) == 1)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_mid(t_cub3d_data *cub, int i, int ret, int j)
{
	int	len;

	len = ft_strlen(cub->matrice[i]) - 1;
	while (len > 0)
	{
		if (!(cub->matrice[i][len] == ' '))
			break ;
		len--;
	}
	if (cub->matrice[i][len] != '1')
		return (FAILURE);
	while (j < len)
	{
		if (valid_char(cub, cub->matrice[i][j], i, j) == FAILURE)
			return (FAILURE);
		else if (cub->matrice[i][j] == '0' || cub->matrice[i][j] == 'N' || \
			cub->matrice[i][j] == 'S' || cub->matrice[i][j] == 'E' || \
			cub->matrice[i][j] == 'W')
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
	if (!cub->line)
		return (FAILURE);
	j = ft_strlen(cub->line);
	if (ft_isspace(cub->line[i]))
	{
		while (ft_isspace(cub->line[i]))
			i++;
		if (!cub->line)
			return (FAILURE);
	}
	i = 0;
	line = ft_strtrim(cub->line, "\n");
	free(cub->line);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (FAILURE);
		else
			i++;
	}
	while (j < cub->m_index)
	{
		if (cub->matrice[j][0] == '\0')
			return (FAILURE);
		j++;
	}
	cub->matrice = ft_split(line, '\n');
	free(line);
	return (SUCCESS);
}

int	check_map(t_cub3d_data *cub)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	if (check_retline(cub) == FAILURE)
		return (FAILURE);
	while (i < cub->m_index)
	{
		if (ft_strlen(cub->matrice[i]) > cub->len_i)
			cub->len_i = ft_strlen(cub->matrice[i]);
		i++;
	}
	cub->len_j = resizematrice(cub, cub->m_index);
	i =0;
	while (i < cub->m_index)
	{
		if (i == 0 || i == cub->m_index - 1)
			ret = parsetopbottom_line(cub);
		else
			ret = parse_mid(cub, i, 1, 1);
		if (ret == FAILURE)
			return (FAILURE);
		i++;
	}
	if (i == cub->m_index && cub->player_dir == '\0')
		return (FAILURE);
	return (ret);
}
