/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:13:01 by nouahidi          #+#    #+#             */
/*   Updated: 2023/07/15 18:37:37 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	ft_hook(void *param)
// {
// 	t_cub3d_data	*cub;
// 	int				y1;
// 	int				x1;
// 	double			turn_dir;
// 	double			walk_dir;
// 	double			side_dir;
// 	double			mv_step;

// 	cub = param;
// 	turn_dir = 0;
// 	walk_dir = 0;
// 	side_dir = 0;
// 	mlx_delete_image(cub->mlx, cub->map_img);
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(cub->mlx);
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
// 	{
// 		turn_dir = 1.0;
// 		if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
// 			turn_dir = -1.0;
// 		cub->player_data->rot_angle += (turn_dir * ROT_SPEED);
// 	}
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 	{
// 		walk_dir = 1.0;
// 		if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 			walk_dir = -1.0;
// 		x1 = cub->player_data->x;
// 		y1 = cub->player_data->y;
// 		mv_step = walk_dir * MV_SPEED;
// 		cub->player_data->x += cos(cub->player_data->rot_angle) * mv_step;
// 		cub->player_data->y += sin(cub->player_data->rot_angle) * mv_step;
//         if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1' 
//         || (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(x1 / WALL_DIMENSION)] == '1' && cub->matrice[(int)(y1 / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1'))
//         {
//             cub->player_data->x = x1;
//             cub->player_data->y = y1;
//         }
//     }
//     if (mlx_is_key_down(cub->mlx, MLX_KEY_D) || mlx_is_key_down(cub->mlx, MLX_KEY_A))
//     {
//         x1 = cub->player_data->x;
//         y1 = cub->player_data->y;
//         side_dir = -1;
//         if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
//             side_dir = 1;
//         mv_step = side_dir * MV_SPEED;
//         cub->player_data->x += cos(cub->player_data->rot_angle + (M_PI / 2)) * mv_step;
//         cub->player_data->y += sin(cub->player_data->rot_angle + (M_PI / 2)) * mv_step;
//         if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1'
//         || (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(x1 / WALL_DIMENSION)] == '1' && cub->matrice[(int)(y1 / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1'))
//         {
//             cub->player_data->x = x1;
//             cub->player_data->y = y1;
//         }
//     }
//     cub_img(cub);
//     mlx_image_to_window(cub->mlx, cub->map_img, 0, 0);
// }

void	ft_hook(void *param)
{
	t_cub3d_data	*cub;
	int				y1;
	int				x1;
	double			turn_dir;
	double			walk_dir;
	double			side_dir;
	double			mv_step;

	cub = param;
	turn_dir = 0;
	walk_dir = 0;
	side_dir = 0;
	mlx_delete_image(cub->mlx, cub->map_img);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		turn_dir = 1.0;
		if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
			turn_dir = -1.0;
		cub->player_data->rot_angle += (turn_dir * ROT_SPEED);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		walk_dir = 1.0;
		if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
			walk_dir = -1.0;
		x1 = cub->player_data->x;
		y1 = cub->player_data->y;
		mv_step = walk_dir * MV_SPEED;
		cub->player_data->x += cos(cub->player_data->rot_angle) * mv_step;
		cub->player_data->y += sin(cub->player_data->rot_angle) * mv_step;
        if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1' 
        || (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(x1 / WALL_DIMENSION)] == '1' && cub->matrice[(int)(y1 / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1') ||
		cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == 'D')
        {
            cub->player_data->x = x1;
            cub->player_data->y = y1;
        }
    }
    if (mlx_is_key_down(cub->mlx, MLX_KEY_D) || mlx_is_key_down(cub->mlx, MLX_KEY_A))
    {
        x1 = cub->player_data->x;
        y1 = cub->player_data->y;
        side_dir = -1;
        if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
            side_dir = 1;
        mv_step = side_dir * MV_SPEED;
        cub->player_data->x += cos(cub->player_data->rot_angle + (M_PI / 2)) * mv_step;
        cub->player_data->y += sin(cub->player_data->rot_angle + (M_PI / 2)) * mv_step;
        if (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1'
        || (cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(x1 / WALL_DIMENSION)] == '1' && cub->matrice[(int)(y1 / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == '1') ||
		cub->matrice[(int)(cub->player_data->y / WALL_DIMENSION)][(int)(cub->player_data->x / WALL_DIMENSION)] == 'D')
        {
            cub->player_data->x = x1;
            cub->player_data->y = y1;
        }
    }
	if (mlx_is_key_down(cub->mlx, MLX_KEY_O))
		cub->openflag = 1;
    cub_img(cub);
    mlx_image_to_window(cub->mlx, cub->map_img, 0, 0);
}
