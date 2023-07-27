/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:06:56 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/27 12:07:52 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

pid_t	play_music(t_cub3d_data *cub, char *path)
{
	char	**args;
	pid_t	pid;

	pid = fork(); 
	if (pid < 0)
	{
		printf("Music process couldn't be forked :(");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args = ft_split(path, ' ');
		execv("/usr/bin/afplay", args);
	}
	return (pid);
}

void	add_sounds(t_cub3d_data *cub, int sound)
{
	pid_t	pid;

	pid = 0;
	if (sound == G)
		pid = play_music(cub, "afplay sounds/gta.mp3");
	else if (sound == K)
		pid = play_music(cub, "afplay sounds/Klaxon.wav");
	else if (sound == C)
		cub->pid = play_music(cub, "afplay sounds/intro.mp3");
	if (pid < 0 || cub->pid < 0)
		exit(EXIT_FAILURE);
}
