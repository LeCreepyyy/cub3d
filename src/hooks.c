/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:11 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/06 15:41:17 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Called every frame by mlx function ft_loop_hook().
 * Mouse and Keyboard handling function. Also handles flashlight.
 * @param param	void *param, used to pass our Data struct.
 */
void	ft_loop(void *param)
{
	t_data	*data;

	data = param;
	ray_view(data);
	if (pos_mouse(data) == 2)
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, 0.07);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 0.07);
	}
	else if (pos_mouse(data) == 1)
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, -0.07);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -0.07);
	}
	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	ft_loop2(data);
}

/**
 * Norm child of ft_loop()
 * @param data Data struct.
 */
void	ft_loop2(t_data *data)
{
	double	speed;

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
	data->imgs.mp_player->instances[0].x = (data->player.pos_x) * MP_WALL;
	data->imgs.mp_player->instances[0].y = (data->player.pos_y) * MP_WALL;
	speed = 1;
}

/**
 * Animate the flashlight hold by the player when walking.
 * @param data Data struct.
 */
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

/**
 * Make the black veil appear/disapprear to imitate the flashlight light beam.
 * @param data Data struct.
 * @param code Flashlight status.
 */
void	action_flashlight(t_data *data, int code)
{
	static int	pass = 1;

	if (code == 1)
	{
		if (pass == 1)
			return ;
		mlx_set_instance_depth(&data->imgs.black->instances[0], -1);
		pass = 1;
	}
	else if (code == 2)
	{
		if (pass != 1)
			return ;
		pass = 0;
		mlx_set_instance_depth(&data->imgs.black->instances[0], 5);
	}
}
