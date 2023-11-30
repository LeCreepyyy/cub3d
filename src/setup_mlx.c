/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/30 11:36:07 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	(void)keydata;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_ptr);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		data->imgs.mp_player->instances[0].y -= 7;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		data->imgs.mp_player->instances[0].y += 7;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		data->imgs.mp_player->instances[0].x -= 7;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		data->imgs.mp_player->instances[0].x += 7;
}

// void	ft_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
// 	if (keydata.action != MLX_PRESS)
// 		return ;
// 	if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
// 		mlx_close_window(data->mlx_ptr);
// 	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
// 		data->imgs.mp_player->instances[0].y -= 10;
// 	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
// 		data->imgs.mp_player->instances[0].y += 10;
// 	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
// 		data->imgs.mp_player->instances[0].x -= 10;
// 	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
// 		data->imgs.mp_player->instances[0].x += 10;
// }

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
				mlx_image_to_window(data->mlx_ptr, data->imgs.mp_wall, x * MP_WALL, y * MP_WALL);
			else if (data->map_flat[y][x] != ' ' && data->map_flat[y][x] != '\n')
				mlx_image_to_window(data->mlx_ptr, data->imgs.mp_floor, x * MP_WALL, y * MP_WALL);
		}
	}
}

void	*px_memset(void *str, uint8_t r, uint8_t g, uint8_t b, uint8_t a, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (i % 4 == 0)
			((uint8_t *)str)[i] = r;
		if (i % 4 == 1)
			((uint8_t *)str)[i] = g;
		if (i % 4 == 2)
			((uint8_t *)str)[i] = b;
		if (i % 4 == 3)
			((uint8_t *)str)[i] = a;
		i++;
	}
	return (str);
}

void	setup_imgs(t_data *data)
{
	data->imgs.wall_north_texture = mlx_load_png(get_texture('N', data));
	data->imgs.wall_north = mlx_texture_to_image(data->mlx_ptr, data->imgs.wall_north_texture);
	data->imgs.wall_south_texture = mlx_load_png(get_texture('S', data));
	data->imgs.wall_south = mlx_texture_to_image(data->mlx_ptr, data->imgs.wall_south_texture);
	data->imgs.wall_east_texture = mlx_load_png(get_texture('E', data));
	data->imgs.wall_east = mlx_texture_to_image(data->mlx_ptr, data->imgs.wall_east_texture);
	data->imgs.wall_west_texture = mlx_load_png(get_texture('W', data));
	data->imgs.wall_west = mlx_texture_to_image(data->mlx_ptr, data->imgs.wall_west_texture);
	data->imgs.mp_wall = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_wall->pixels, 16, 52, 166, 255, MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_floor = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_floor->pixels, 169, 234, 254, 255, MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_player = mlx_new_image(data->mlx_ptr, MP_PLAYER, MP_PLAYER);
	px_memset(data->imgs.mp_player->pixels, 164, 36, 36, 255, MP_PLAYER * MP_PLAYER * sizeof(int));
}

void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(1680, 1024, "Qbe 3D", false);
	setup_imgs(data);
	minimap(data);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_player, 200, 200);
	mlx_key_hook(data->mlx_ptr, ft_hook, data);
	mlx_loop(data->mlx_ptr);
}
