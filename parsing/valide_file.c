/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 22:37:31 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/19 22:52:44 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

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
