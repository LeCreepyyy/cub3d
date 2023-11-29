/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 18:13:25 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_square(int x, int y, mlx_image_t i, t_data *data)
// {
// 	mlx_image_to_window(data->mlx_ptr, data->img, x, y);
// }

// void	minimap(t_data *data)
// {
// 	print_square(0, 0, NULL, data);
// 	print_square(MP_WALL, 0, NULL, data);
// }

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
	ft_memset(data->imgs.mp_wall->pixels, WHITE, MP_WALL * MP_WALL * sizeof(int32_t));
	data->imgs.mp_player = mlx_new_image(data->mlx_ptr, MP_PLAYER, MP_PLAYER);
	ft_memset(data->imgs.mp_player->pixels, ORANGE, MP_PLAYER * MP_PLAYER * sizeof(int32_t));
	// taille des images de sol et plafond ? ->
	data->imgs.floor = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	ft_memset(data->imgs.floor->pixels, GREEN, MP_WALL * MP_WALL * sizeof(int32_t));
	data->imgs.ceiling = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
	ft_memset(data->imgs.ceiling->pixels, BLUE, MP_WALL * MP_WALL * sizeof(int32_t));
}

void	setup_mlx(t_data *data)
{
	//data->mlx_ptr = mlx_init(1480, 1024, "cub3d", false);
	data->mlx_ptr = mlx_init(600, 480, "cub3d - VM", false);
	setup_imgs(data);
	mlx_image_to_window(data->mlx_ptr, data->imgs.wall_north, 0, 0);
	mlx_image_to_window(data->mlx_ptr, data->imgs.wall_south, 50, 50);
	mlx_image_to_window(data->mlx_ptr, data->imgs.wall_east, 100, 100);
	mlx_image_to_window(data->mlx_ptr, data->imgs.wall_west, 150, 150);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_player, 200, 200);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_wall, 250, 250);
	mlx_image_to_window(data->mlx_ptr, data->imgs.floor, 300, 300);
	mlx_image_to_window(data->mlx_ptr, data->imgs.ceiling, 350, 350);
	//minimap(data);
	mlx_loop(data->mlx_ptr);
}
