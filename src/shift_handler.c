/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:35:09 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/03 13:13:36 by vpoirot          ###   ########.fr       */
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
	int mouse_x = 0;
	int mouse_y = 0;

	mlx_get_mouse_pos(data->mlx_ptr, &mouse_x, &mouse_y);
	if (mouse_x <= 150)
		return (1);
	else if (mouse_x >= 600)
		return (2);
	return (0);
}

void	ft_shift_handle(t_data *data, double rotspeed, double speed)
{
	double	dir_x = data->player.dir_x;
	double	dir_y = data->player.dir_y;

	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
		ft_next_pos(data, dir_x, dir_y, speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
		ft_next_pos(data, dir_x, dir_y, -speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
	{
		ft_rotate_point(&dir_x, &dir_y, -7.9);
		ft_next_pos(data, dir_x, dir_y, speed);
		ft_rotate_point(&dir_x, &dir_y, 7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
	{
		ft_rotate_point(&dir_x, &dir_y, 7.9);
		ft_next_pos(data, dir_x, dir_y, speed);
		ft_rotate_point(&dir_x, &dir_y, -7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
		ft_rotate_point(&dir_x, &dir_y, rotspeed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT) && ray_view(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y) == NULL)
		ft_rotate_point(&dir_x, &dir_y, -rotspeed);
	data->player.dir_x = dir_x;
	data->player.dir_y = dir_y;
}

/*
void	ft_hook(mlx_key_data_t keydata, void *param)
{
	double			speed;
	double			rotspeed;
	t_data			*data;
	static double	dir_x = -1;
	static double	dir_y = 0;

	data = param;
	(void)keydata;
	speed = 4.0;
	rotspeed = 0.1;
	data->player.pos_x = data->imgs.mp_player->instances[0].x;
	data->player.pos_y = data->imgs.mp_player->instances[0].y;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT_SHIFT))
		speed = 7;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_ptr);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		ft_next_pos(data, dir_x, dir_y, speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		ft_next_pos(data, dir_x, dir_y, -speed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
	{
		ft_rotate_point(&dir_x, &dir_y, -7.9);
		ft_next_pos(data, dir_x, dir_y, speed);
		ft_rotate_point(&dir_x, &dir_y, 7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
	{
		ft_rotate_point(&dir_x, &dir_y, 7.9);
		ft_next_pos(data, dir_x, dir_y, speed);
		ft_rotate_point(&dir_x, &dir_y, -7.9);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		ft_rotate_point(&dir_x, &dir_y, rotspeed);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		ft_rotate_point(&dir_x, &dir_y, -rotspeed);
	data->imgs.mp_player->instances[0].x = round(data->player.pos_x);
	data->imgs.mp_player->instances[0].y = round(data->player.pos_y);
	speed = 4.0;
}
*/
