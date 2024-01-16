/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/16 15:09:11 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Draws minimap.
 * @param data Data struct.
 */
void	minimap(t_data *data)
{
	int		y;
	int		x;

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
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_player,
		data->player_pos[1] * MP_WALL, data->player_pos[2] * MP_WALL);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_ray, 0, 0);
}

/**
 * Sets the values of memory block to the RGBA color provided.
 * @param str Pointer to memory block.
 * @param color Struct of RGBA data
 * @param len Length of the memory block
 * @return Pointer to memory block
 */
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

/**
 * Images loading, textures creations, pixel memory setting.
 * @param data Data struct. 
 */
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
	setup_imgs2(data);
}

/**
 * Norm child of setup_imgs()
 * @param data Data struct. 
 */
void	setup_imgs2(t_data *data)
{
	data->imgs.ceiling = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT / 2);
	px_memset(data->imgs.ceiling->pixels, data->colors.ceilling,
		WIDTH * (HEIGHT / 2) * sizeof(int));
	data->imgs.floor = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT / 2);
	px_memset(data->imgs.floor->pixels, data->colors.floor,
		WIDTH * (HEIGHT / 2) * sizeof(int));
	data->imgs.graph = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->imgs.mp_wall = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_wall->pixels, data->colors.dark_blue,
		MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_floor = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	px_memset(data->imgs.mp_floor->pixels, data->colors.light_blue,
		MP_WALL * MP_WALL * sizeof(int));
	data->imgs.mp_player = mlx_new_image(data->mlx_ptr, MP_PLAYER, MP_PLAYER);
	px_memset(data->imgs.mp_player->pixels, data->colors.red,
		MP_PLAYER * MP_PLAYER * sizeof(int));
	data->imgs.mp_ray = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
}


/**
 * Entry points of MLX and graphical functions.
 * @param data Data struct.
 */
void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Qbe 3D", false);
	mlx_set_window_pos(data->mlx_ptr, 960, 720);
	init_colors_cf(data);
	setup_imgs(data);
	mlx_image_to_window(data->mlx_ptr, data->imgs.ceiling, 0, 0);
	mlx_image_to_window(data->mlx_ptr, data->imgs.floor, 0, 512);
	minimap(data);
	if (data->player_pos[0] == 'N')
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 7.9);
	else if (data->player_pos[0] == 'E')
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, 7.9 * 2);
	else if (data->player_pos[0] == 'S')
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -7.9);
	data->player.pos_x = data->imgs.mp_player->instances[0].x;
	data->player.pos_y = data->imgs.mp_player->instances[0].y;
	mlx_set_cursor_mode(data->mlx_ptr, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	ray_view(data);
	mlx_key_hook(data->mlx_ptr, ft_hook, data);
	//mlx_loop_hook(data->mlx_ptr, ft_loop, data);
	mlx_loop(data->mlx_ptr);
}
