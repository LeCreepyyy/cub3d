/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:35:09 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/05 13:36:46 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *data, int y, int x)
{
	if (data->map_flat[y / MP_WALL][x / MP_WALL] == '1'
		|| data->map_flat[(y + MP_PLAYER) / MP_WALL]
			[(x + MP_PLAYER) / MP_WALL] == '1'
		|| data->map_flat[(y + MP_PLAYER) / MP_WALL][x / MP_WALL] == '1'
		|| data->map_flat[y / MP_WALL][(x + MP_PLAYER) / MP_WALL] == '1')
		return (0);
	return (1);
}

void	ft_next_pos(t_data *data, double dir_x, double dir_y, double speed)
{
	if (is_wall(data, data->player.pos_y, data->player.pos_x + dir_x * speed))
		data->player.pos_x += dir_x * speed;
	if (is_wall(data, data->player.pos_y + dir_y * speed, data->player.pos_x))
		data->player.pos_y += dir_y * speed;
}

void	ft_rotate_point(double *dir_x, double *dir_y, double rotspeed)
{
	double	old_x;

	old_x = *dir_x;
	*dir_x = *dir_x * cos(rotspeed) - *dir_y * sin(rotspeed);
	*dir_y = old_x * sin(rotspeed) + *dir_y * cos(rotspeed);
}

int	pos_mouse(t_data *data)
{
	int	mouse_x;
	int	mouse_y;

	mouse_x = 0;
	mouse_y = 0;
	mlx_get_mouse_pos(data->mlx_ptr, &mouse_x, &mouse_y);
	if (mouse_x < WIDTH / 2)
		return (1);
	if (mouse_x > WIDTH / 2)
		return (2);
	return (0);
}

void	ft_shift_handle(t_data *data, double rotspeed, double speed)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		ft_next_pos(data, data->player.dir_x, data->player.dir_y, speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		ft_next_pos(data, data->player.dir_x, data->player.dir_y, -speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
	{
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -7.9);
		ft_next_pos(data, data->player.dir_x, data->player.dir_y, speed);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
	{
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 7.9);
		ft_next_pos(data, data->player.dir_x, data->player.dir_y, speed);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, rotspeed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -rotspeed);
	ray_view(data);
}
