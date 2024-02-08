/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:35:09 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/08 10:49:00 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Player movement and walls collision
 * @param data Data struct.
 * @param dir_x The direction in the x-axis that the player is moving in.
 * @param dir_y The direction in the y-axis that the player is moving in.
 * @param speed Movement speed.
 */
void	ft_next_pos(t_data *data, double dir_x, double dir_y, double speed)
{
	if (is_wall(data, data->player.pos_y, data->player.pos_x + dir_x * speed))
	{
		ft_flashlight(data);
		data->player.pos_x += dir_x * speed;
	}
	if (is_wall(data, data->player.pos_y + dir_y * speed, data->player.pos_x))
	{
		ft_flashlight(data);
		data->player.pos_y += dir_y * speed;
	}
}

/**
 * Rotates points by a given rotation speed.
 * @param dir_x x-coordinate of the direction vector to rotate.
 * @param dir_y y-coordinate of the direction vector to rotate.
 * @param rotspeed Rotation speed in radians.
 */
void	ft_rotate_point(double *dir_x, double *dir_y, double rotspeed)
{
	double	old_x;

	old_x = *dir_x;
	*dir_x = *dir_x * cos(rotspeed) - *dir_y * sin(rotspeed);
	*dir_y = old_x * sin(rotspeed) + *dir_y * cos(rotspeed);
}

/**
 * Checks if mouse is left or right form the middle of the window.
 * @param data Data struct.
 * @return 1 if left, 2 if right, 0 otherwise.
 */
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

/**
 * Movement handling function.
 * @param data Data struct
 * @param rotspeed Player's rotation speed
 * @param speed Player's movement speed
 */
void	ft_key_handler(t_data *data, double rotspeed, double speed)
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
	ft_key_handler2(data, rotspeed);
}

/**
 * Norm child of ft_key_handler()
 * @param data Data struct
 * @param rotspeed Player's rotation speed
 */
void	ft_key_handler2(t_data *data, double rotspeed)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, rotspeed);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, rotspeed);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y,
			-rotspeed);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -rotspeed);
	}
}
