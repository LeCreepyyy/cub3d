/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/22 11:45:51 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Determines wich texture to display.
 * @param data Data struct
 * @param i Ray index
 * @param px Player x-coords
 * @param py Player y-coords
 * @return North South East West
 */
mlx_image_t	*get_texture_orientation(t_data *data, int i, double px, double py)
{
	if (fmod(data->rays.collision_x[i], 1.0) == 0.0)
	{
		if (px < data->rays.collision_x[i])
			return (data->imgs.wall_west);
		if (px > data->rays.collision_x[i])
			return (data->imgs.wall_east);
	}
	else if (fmod(data->rays.collision_y[i], 1.0) == 0.0)
	{
		if (py < data->rays.collision_y[i])
			return (data->imgs.wall_south);
		if (py > data->rays.collision_y[i])
			return (data->imgs.wall_north);
	}
}

/**
 * Determines wich texture strip to display.
 * 
 * @param data Data struct
 */
void	get_texture_strip(t_data *data)
{
	int	i;

	i = -1;
	while (data->rays.length[++i])
	{
		data->rays.wall = get_texture_orientation(data, i, data->player.pos_x, data->player.pos_y);
	}
}
