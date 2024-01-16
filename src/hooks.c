/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:11 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/16 15:18:16 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	double			speed;
	t_data			*data;

	data = param;
	(void)keydata;
	speed = 1;
	data->player.pos_x = data->imgs.mp_player->instances[0].x;
	data->player.pos_y = data->imgs.mp_player->instances[0].y;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT_SHIFT))
		speed = 4.0;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_ptr);
	ft_key_handler(data, 0.1, speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_SPACE))
	{
		if (pos_mouse(data) == 2)
		{
			ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 0.09);
			ray_view(data);
		}
		if (pos_mouse(data) == 1)
		{
			ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -0.09);
			ray_view(data);
		}
		mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	}
	data->imgs.mp_player->instances[0].x = round(data->player.pos_x);
	data->imgs.mp_player->instances[0].y = round(data->player.pos_y);
	speed = 1;
}

// void	ft_loop(void *param)
// {
// 	t_data	*data;

// 	data = param;
// 	(void)data;
// 	if (pos_mouse(data) == 2)
// 	{
// 		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 0.05);
// 		ray_view(data);
// 	}
// 	if (pos_mouse(data) == 1)
// 	{
// 		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -0.05);
// 		ray_view(data);
// 	}
// 	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
// }
