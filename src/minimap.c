/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:43:13 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/19 11:51:37 by bgaertne         ###   ########.fr       */
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
			print_minimap_walls_and_floor(data, x, y);
	}
	print_minimap_player_and_rays(data);
}

void	print_minimap_walls_and_floor(t_data *data, int x, int y)
{
	if (data->map_flat[y][x] == '1')
	{
		mlx_image_to_window(data->mlx_ptr, data->imgs.mp_wall,
			x * MP_WALL, y * MP_WALL);
		mlx_set_instance_depth(&data->imgs.mp_wall->instances[data->imgs.mp_wc],
			2);
		data->imgs.mp_wc++;
	}
	else if (data->map_flat[y][x] != ' ' && data->map_flat[y][x] != '\n')
	{
		mlx_image_to_window(data->mlx_ptr, data->imgs.mp_floor,
			x * MP_WALL, y * MP_WALL);
		mlx_set_instance_depth(&data->imgs.mp_floor->instances[data->imgs.mpfc],
			2);
		data->imgs.mpfc++;
	}
}

void	print_minimap_player_and_rays(t_data *data)
{
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_player,
		data->player_pos[1] * MP_WALL, data->player_pos[2] * MP_WALL);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_ray, 0, 0);
	mlx_set_instance_depth(&data->imgs.mp_player->instances[0], 4);
	mlx_set_instance_depth(&data->imgs.mp_ray->instances[0], 3);
}
