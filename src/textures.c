/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/24 14:42:20 by bgaertne         ###   ########.fr       */
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
int	get_texture_orientation(t_data *data, int i, double px, double py)
{
	if ((int)data->rays[i].collision_x % 20 == 0)
	{
		if (py <= data->rays[i].collision_y)
		{
			if (i == 0)
				printf("SOUTH %i\n", (int)data->rays[i].collision_y % 20);
			return (SOUTH);
		}
		if (py >= data->rays[i].collision_y)
		{
			if (i == 0)
				printf("NORTH %i\n", (int)data->rays[i].collision_y % 20);
			return (NORTH);
		}
	}
	if ((int)data->rays[i].collision_y % 20 == 0)
	{
		if (px <= data->rays[i].collision_x)
		{
			if (i == 0)
				printf("EAST %i\n", (int)data->rays[i].collision_y % 20);
			return (EAST);
		}
		if (px >= data->rays[i].collision_x)
		{
			if (i == 0)
				printf("WEST %i\n", (int)data->rays[i].collision_y % 20);
			return (WEST);
		}
	}
	return (0);
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
	orient = 0;
	while (data->rays[++i].length)
	{
		orient = get_texture_orientation(data, i, data->player.pos_x, data->player.pos_y);
		//if (i == 0)
			//printf("orient: %i\n", orient);
		data->rays[i].orient = orient;
		if (orient == NORTH)
		{
			data->rays[i].wall = data->imgs.wall_north;
			data->rays[i].strip_x = data->rays[i].collision_x - fmod(data->rays[i].collision_x, 1.0);
		}
		if (orient == SOUTH)
		{
			data->rays[i].wall = data->imgs.wall_south;
			data->rays[i].strip_x = data->rays[i].collision_x - fmod(data->rays[i].collision_x, 1.0);
		}
		if (orient == EAST)
		{
			data->rays[i].wall = data->imgs.wall_east;
			data->rays[i].strip_x = data->rays[i].collision_y - fmod(data->rays[i].collision_y, 1.0);
		}
		if (orient == WEST)
		{
			data->rays[i].wall = data->imgs.wall_west;
			data->rays[i].strip_x = data->rays[i].collision_y - fmod(data->rays[i].collision_y, 1.0);
		}
	}
}
