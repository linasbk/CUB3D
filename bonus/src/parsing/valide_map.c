/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:58:30 by lsabik            #+#    #+#             */
/*   Updated: 2023/07/23 12:52:17 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_bottom(t_cub3d_data *cub)
{
	int	i;

	i = 0;
	while (cub->matrice[cub->m_index - 1][i])
	{
		if (cub->matrice[cub->m_index - 1][i] == '1')
			i++;
		else if (ft_isspace(cub->matrice[cub->m_index - 1][i]))
		{
			if (ft_strlen(cub->matrice[cub->m_index - 1]) <= ft_strlen(\
			cub->matrice[cub->m_index - 2]) && cub->matrice[cub->m_index - 2] \
			[i] != ' ' && cub->matrice[cub->m_index - 2][i] != '1')
				return (FAILURE);
			else
				i++;
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

int	parsetopbottom_line(t_cub3d_data *cub)
{
	int	i;

	i = 0;
	while (cub->matrice[0][i])
	{
		if (cub->matrice[0][i] == '1')
			i++;
		else if (ft_isspace(cub->matrice[0][i]))
		{
			if (ft_strlen(cub->matrice[0]) <= ft_strlen(cub->matrice[1]) && \
				cub->matrice[1][i] != ' ' && cub->matrice[1][i] != '1')
				return (FAILURE);
			else
				i++;
		}
		else
			return (FAILURE);
	}
	return (parse_bottom(cub));
}

int	check_sides(t_cub3d_data *cub, int i, int j)
{
	if (ft_strlen(cub->matrice[i]) <= ft_strlen(cub->matrice[i - 1]))
	{
		if (!(check_space(cub->matrice[i - 1][j]) == 1 || cub->matrice[i - 1] \
			[j] == '1' || cub->matrice[i - 1][j] == '\0'))
			return (FAILURE);
	}
	if (ft_strlen(cub->matrice[i]) <= ft_strlen(cub->matrice[i + 1]))
	{
		if (!(check_space(cub->matrice[i + 1][j]) == 1 || cub->matrice[i + 1] \
			[j] == '1' || cub->matrice[i + 1][j] == '\0'))
			return (FAILURE);
	}
	if (cub->matrice[i][j - 1])
	{
		if (!(check_space(cub->matrice[i][j - 1]) == 1 || cub->matrice[i] \
			[j - 1] == '1' || cub->matrice[i][j - 1] == '\0'))
			return (FAILURE);
	}
	if (cub->matrice[i][j + 1])
	{
		if (!(check_space(cub->matrice[i][j + 1]) == 1 || cub->matrice[i] \
			[j + 1] == '1' || cub->matrice[i][j + 1] == '\0'))
			return (FAILURE);
	}
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
		else if (cub->matrice[i][j] == ' ')
			ret = check_sides(cub, i, j);
		if (ret == FAILURE)
			return (FAILURE);
		j++;
	}
	return (ret);
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
	cub->len_j = resizematrice(cub, cub->m_index);
	return (ret);
}
