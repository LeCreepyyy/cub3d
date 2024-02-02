/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:11 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/02 14:07:47 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	compass(double dir_x, double dir_y)
{
	double	base_x;
	double	base_y;
	double	angle;

	base_x = -1;
	base_y = 0;
	angle = atan2(dir_x, dir_y) - atan2(base_x, base_y);
	return (angle);
}

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
	if (pos_mouse(data) == 1)
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, 0.05);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 0.05);
	}
	else if (pos_mouse(data) == 2)
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, -0.05);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -0.05);
	}
	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	speed = 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT_SHIFT))
		speed = 0.15;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_ptr);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_P))
		action_flashlight(data, 2);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_L))
		action_flashlight(data, 1);
	ft_key_handler(data, 0.01, speed);
	data->imgs.mp_player->instances[0].x = round(data->player.pos_x) * MP_WALL;
	data->imgs.mp_player->instances[0].y = round(data->player.pos_y) * MP_WALL;
	speed = 1;
}

void	action_flashlight(t_data *data, int code)
{
	static int	pass = 1;

	if (code == 1)
	{
		if (pass == 1)
			return ;
		mlx_delete_image(data->mlx_ptr, data->imgs.black);
		mlx_delete_texture(data->imgs.black_txtr);
		pass = 1;
	}
	else if (code == 2)
	{
		if (pass != 1)
			return ;
		pass = 0;
		data->imgs.black_txtr = mlx_load_png("resources/black.png");
		data->imgs.black = mlx_texture_to_image(data->mlx_ptr,
				data->imgs.black_txtr);
		mlx_image_to_window(data->mlx_ptr, data->imgs.black, 0, -100);
		mlx_set_instance_depth(&data->imgs.black->instances[0], 5);
	}
}
