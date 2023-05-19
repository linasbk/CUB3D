/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:21:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/05/19 22:50:21 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d_data	*cub;

	cub = malloc(sizeof(t_cub3d_data));
	if (map_parsing(cub, ac, av) == FAILURE)
		return (FAILURE);
}
