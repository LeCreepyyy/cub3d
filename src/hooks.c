/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:11 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/25 15:51:34 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_flashlight(t_data *data)
{
	static int		time_diff = 0;

	if (time_diff < 20)
		data->imgs.flash->instances[0].y -= 1;
	if (time_diff >= 20 && time_diff < 40)
		data->imgs.flash->instances[0].y += 1;
	time_diff++;
	if (time_diff >= 40)
		time_diff = 0;
}

void	ft_loop(void *param)
{
	t_data	*data;
	double	speed;

	data = param;
	ray_view(data);
	if (pos_mouse(data) == 2)
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 0.05);
	else if (pos_mouse(data) == 1)
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -0.05);
	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	speed = 1.0;
	data->player.pos_x = data->imgs.mp_player->instances[0].x;
	data->player.pos_y = data->imgs.mp_player->instances[0].y;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT_SHIFT))
		speed = 2.0;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_ptr);
	ft_key_handler(data, 0.01, speed);
	data->imgs.mp_player->instances[0].x = round(data->player.pos_x);
	data->imgs.mp_player->instances[0].y = round(data->player.pos_y);
	speed = 1;
}
