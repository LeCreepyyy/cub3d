/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/09 12:24:06 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks for wall resolutions (>42px, all equals, and all square)
 * @param data Data struct. 
 */
void	check_wall_resolution(t_data *data)
{
	if (data->imgs.wall_north->width < 42
		|| data->imgs.wall_south->width < 42
		|| data->imgs.wall_east->width < 42
		|| data->imgs.wall_west->width < 42)
		return (ft_exit("Textures are too small (>42px)", 1));
	if (data->imgs.wall_north->width != data->imgs.wall_north->height
		|| data->imgs.wall_south->width != data->imgs.wall_south->height
		|| data->imgs.wall_east->width != data->imgs.wall_east->height
		|| data->imgs.wall_west->width != data->imgs.wall_west->height)
		return (ft_exit("Textures are not square", 1));
	if (data->imgs.wall_north->width == data->imgs.wall_south->width
		&& data->imgs.wall_south->width == data->imgs.wall_east->width
		&& data->imgs.wall_east->width == data->imgs.wall_west->width)
		data->imgs.wall_resolution = data->imgs.wall_north->width;
	else
		return (ft_exit("Textures needs to be of the same resolution", 1));
}

/**
 * Images loading, textures creations, pixel memory setting.
 * @param data Data struct. 
 */
void	setup_imgs(t_data *data)
{
	data->imgs.wall_north_texture = mlx_load_png(get_texture('N', data));
	data->imgs.wall_south_texture = mlx_load_png(get_texture('S', data));
	data->imgs.wall_east_texture = mlx_load_png(get_texture('E', data));
	data->imgs.wall_west_texture = mlx_load_png(get_texture('W', data));
	data->imgs.flash_txtr = mlx_load_png("resources/hand_texture.png");
	data->imgs.black_txtr = mlx_load_png("resources/black.png");
	if (!data->imgs.wall_north_texture || !data->imgs.wall_south_texture
		|| !data->imgs.wall_east_texture || !data->imgs.wall_west_texture
		|| !data->imgs.flash_txtr || !data->imgs.black_txtr)
		ft_exit("Loading textures failed.", 1);
	data->imgs.wall_north = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_north_texture);
	data->imgs.wall_south = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_south_texture);
	data->imgs.wall_east = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_east_texture);
	data->imgs.wall_west = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.wall_west_texture);
	check_wall_resolution(data);
	data->imgs.flash = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.flash_txtr);
	data->imgs.black = mlx_texture_to_image(data->mlx_ptr,
			data->imgs.black_txtr);
	setup_imgs2(data);
}

/**
 * Norm child of setup_imgs()
 * @param data Data struct. 
 */
void	setup_imgs2(t_data *data)
{
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
	data->imgs.icon_texture = mlx_load_png("resources/cub3dlogo.png");
	mlx_set_icon(data->mlx_ptr, data->imgs.icon_texture);
}

/**
 * Entry points of MLX and graphical functions.
 * @param data Data struct.
 */
void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Qbe 3D", false);
	mlx_set_window_pos(data->mlx_ptr, 200, 20);
	init_colors_cf(data);
	setup_imgs(data);
	mlx_image_to_window(data->mlx_ptr, data->imgs.black, 0, -100);
	mlx_set_instance_depth(&data->imgs.black->instances[0], -1);
	minimap(data);
	mlx_image_to_window(data->mlx_ptr, data->imgs.flash, 400, 600);
	mlx_set_instance_depth(&data->imgs.flash->instances[0], 6);
	player_base_orientation(data);
	data->player.pos_x = (double)data->player_pos[1];
	data->player.pos_y = (double)data->player_pos[2];
	mlx_set_cursor_mode(data->mlx_ptr, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	ray_view(data);
	mlx_loop_hook(data->mlx_ptr, ft_loop, data);
	mlx_loop(data->mlx_ptr);
}

/**
 * Sets the player's orientation according to the map spawn point.
 * @param data Data struct.
 */
void	player_base_orientation(t_data *data)
{
	if (data->player_pos[0] == 'N')
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, PI / 2);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, PI / 2);
	}
	else if (data->player_pos[0] == 'E')
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y, PI);
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, PI);
	}
	else if (data->player_pos[0] == 'S')
	{
		ft_rotate_point(&data->player.plane_x, &data->player.plane_y,
			-(PI / 2));
		ft_rotate_point(&data->player.dir_x, &data->player.dir_y, -(PI / 2));
	}
}
