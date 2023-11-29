/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 17:39:13 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_square(int x, int y, mlx_image_t i, t_data *data)
// {
// 	data->img = mlx_new_image(data->mlx_ptr, MP_WALL, MP_WALL);
// 	ft_memset(data->img->pixels, 255, data->img->width * data->img->height * sizeof(int32_t));
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
}

void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(1480, 1024, "cub3d", false);
	setup_imgs(data);
	//minimap(data);
	mlx_loop(data->mlx_ptr);
}
