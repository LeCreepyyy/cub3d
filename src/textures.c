/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/25 15:46:07 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_texture_orientation(t_data *data, int i, double px, double py)
// {
// 	if (data->rays[i].collision_axis == 'x')
// 	{
// 		if (py <= data->rays[i].collision_y)
// 			return (SOUTH);
// 		else
// 			return (NORTH);
// 	}
// 	else if (data->rays[i].collision_axis == 'y')
// 	{
// 		if (px <= data->rays[i].collision_x)
// 			return (EAST);
// 		else
// 			return (WEST);
// 	}
// 	return (0);
// }

/**
 * Determines wich texture to display.
 * @param data Data struct
 * @param i Ray index
 * @param px Player x-coords
 * @param py Player y-coords
 * 
 * 1+2=3 = N,E
 * 3+4=7 = W,S
 * 1+3=4 = N,W
 * 2+4=6 = E,S
 * 
 * @return North South East West
 */
int	get_texture_orientation(t_data *data, int i, double px, double py)
{
	int	orient_value;

	orient_value = 0;
	if (data->rays[i].collision_x > px)
		orient_value += EAST;
	else
		orient_value += WEST;
	if (data->rays[i].collision_y > py)
		orient_value += SOUTH;
	else
		orient_value += NORTH;
	return (orient_value);
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
		if (orient == 3 && data->rays[i].collision_x - (int)round(data->rays[i].collision_x)!= 0.0)
			data->rays[i].orient = EAST;
		else if (orient == 3)
			data->rays[i].orient = NORTH;
		if (orient == 7 && data->rays[i].collision_x - (int)round(data->rays[i].collision_x)!= 0.0)
			data->rays[i].orient = WEST;
		else if (orient == 7)
			data->rays[i].orient = SOUTH;
		if (orient == 4 && data->rays[i].collision_x - (int)round(data->rays[i].collision_x)!= 0.0)
			data->rays[i].orient = WEST;
		else if (orient == 4)
			data->rays[i].orient = NORTH;
		if (orient == 6 && data->rays[i].collision_x - (int)round(data->rays[i].collision_x)!= 0.0)
			data->rays[i].orient = EAST;
		else if (orient == 6)
			data->rays[i].orient = SOUTH;
	}
}
