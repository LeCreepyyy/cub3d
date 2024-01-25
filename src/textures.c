/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/25 11:02:44 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


	// if ((int)data->rays[i].collision_x % 20 == 0)
	// {
	// 	if (py <= data->rays[i].collision_y)
	// 	{
	// 		if (i == 0)
	// 			printf("SOUTH %i\n", (int)data->rays[i].collision_y % 20);
	// 		return (SOUTH);
	// 	}
	// 	if (py >= data->rays[i].collision_y)
	// 	{
	// 		if (i == 0)
	// 			printf("NORTH %i\n", (int)data->rays[i].collision_y % 20);
	// 		return (NORTH);
	// 	}
	// }
	// if ((int)data->rays[i].collision_y % 20 == 0)
	// {
	// 	if (px <= data->rays[i].collision_x)
	// 	{
	// 		if (i == 0)
	// 			printf("EAST %i\n", (int)data->rays[i].collision_y % 20);
	// 		return (EAST);
	// 	}
	// 	if (px >= data->rays[i].collision_x)
	// 	{
	// 		if (i == 0)
	// 			printf("WEST %i\n", (int)data->rays[i].collision_y % 20);
	// 		return (WEST);
	// 	}
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
