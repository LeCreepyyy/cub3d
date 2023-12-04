/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2023/12/04 15:14:25 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	double			speed;
	double			rotspeed;
	t_data			*data;
	static double	dirX = -1;
	static double	dirY = 0;

	data = param;
	(void)keydata;
	speed = 4.0;
	rotspeed = 2.0;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT_SHIFT))
		speed = 7;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE)
		|| mlx_is_key_down(data->mlx_ptr, MLX_KEY_Q))
		mlx_close_window(data->mlx_ptr);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_UP))
	{
		data->imgs.mp_player->instances[0].x += dirX * speed;
		data->imgs.mp_player->instances[0].y += dirY * speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_DOWN))
	{
		data->imgs.mp_player->instances[0].x -= dirX * speed;
		data->imgs.mp_player->instances[0].y -= dirY * speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
	{
		double	oldX = dirX;
		dirX = dirX * cos(-rotspeed) - dirY * sin(-rotspeed);
		dirY = oldX * sin(-rotspeed) + dirY * cos(-rotspeed);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
	{
		double	oldX = dirX;
		dirX = dirX * cos(-rotspeed) - dirY * sin(-rotspeed);
		dirY = oldX * sin(-rotspeed) + dirY * cos(-rotspeed);
	}
	speed = 4;
}

void	minimap(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map_flat[++y] != NULL)
	{
		x = -1;
		while (data->map_flat[y][++x] != 0)
		{
			if (data->map_flat[y][x] == '1')
				mlx_image_to_window(data->mlx_ptr, data->imgs.mp_wall,
					x * MP_WALL, y * MP_WALL);
			else if (data->map_flat[y][x] != ' '
				&& data->map_flat[y][x] != '\n')
				mlx_image_to_window(data->mlx_ptr, data->imgs.mp_floor,
					x * MP_WALL, y * MP_WALL);
		}
	}
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_player, 1146, 487);
}

void	*px_memset(void *str, struct s_rgba color, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (i % 4 == 0)
			((uint8_t *)str)[i] = color.r;
		if (i % 4 == 1)
			((uint8_t *)str)[i] = color.g;
		if (i % 4 == 2)
			((uint8_t *)str)[i] = color.b;
		if (i % 4 == 3)
			((uint8_t *)str)[i] = color.a;
		i++;
	}
	return (str);
}

void	setup_imgs(t_data *data)
{
	data->imgs.wall_north_texture = mlx_load_png(get_texture('N', data));
	data->imgs.wall_north = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_north_texture);
	data->imgs.wall_south_texture = mlx_load_png(get_texture('S', data));
	data->imgs.wall_south = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_south_texture);
	data->imgs.wall_east_texture = mlx_load_png(get_texture('E', data));
	data->imgs.wall_east = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_east_texture);
	data->imgs.wall_west_texture = mlx_load_png(get_texture('W', data));
	data->imgs.wall_west = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_west_texture);
	data->imgs.mp_wall = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_wall->pixels, data->colors.dark_blue,
		MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_floor = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_floor->pixels, data->colors.light_blue,
		MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_player = mlx_new_image(data->mlx_ptr, MP_PLAYER, MP_PLAYER);
	px_memset(data->imgs.mp_player->pixels, data->colors.red,
		MP_PLAYER * MP_PLAYER * sizeof(int));
}

void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(1680, 1024, "Qbe 3D", false);
	setup_imgs(data);
	minimap(data);
	mlx_key_hook(data->mlx_ptr, ft_hook, data);
	mlx_loop(data->mlx_ptr);
}
