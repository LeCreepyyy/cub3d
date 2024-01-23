/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/23 13:26:48 by bgaertne         ###   ########.fr       */
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
int get_texture_orientation(t_data *data, int i, double px, double py)
{
	if (fmod(data->rays[i].collision_x, 1.0) == 0.0)
	{
		if (px < data->rays[i].collision_x)
			return (4);
		if (px > data->rays[i].collision_x)
			return (3);
	}
	else if (fmod(data->rays[i].collision_y, 1.0) == 0.0)
	{
		if (py < data->rays[i].collision_y)
			return (2);
		if (py > data->rays[i].collision_y)
			return (1);
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
	int	orient;

	i = -1;

	while (data->rays[++i].length)
	{
		orient = get_texture_orientation(data, i, data->player.pos_x, data->player.pos_y);
		if (orient == 1)
		{
			data->rays[i].wall = data->imgs.wall_north;
			data->rays[i].strip_x = data->rays[i].collision_x - fmod(data->rays[i].collision_x, 1.0);
		}
		if (orient == 2)
		{
			data->rays[i].wall = data->imgs.wall_south;
			data->rays[i].strip_x = data->rays[i].collision_x - fmod(data->rays[i].collision_x, 1.0);
		}
		if (orient == 3)
		{
			data->rays[i].wall = data->imgs.wall_east;
			data->rays[i].strip_x = data->rays[i].collision_y - fmod(data->rays[i].collision_y, 1.0);
		}
		if (orient == 4)
		{
			data->rays[i].wall = data->imgs.wall_west;
			data->rays[i].strip_x = data->rays[i].collision_y - fmod(data->rays[i].collision_y, 1.0);
		}
	}
}
