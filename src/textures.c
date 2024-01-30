/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/30 17:26:07 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_orientation(t_data *data, int i)
{
	if (data->rays[i].collision_x % 20 == 19 && data->rays[i].collision_y % 20 != 19)
	{
		data->rays[i].texture_x = (data->rays[i].collision_y % 20);
		if (data->rays[i].compass <= 1.57)
			return (WEST);
		else
			return (EAST);
	}
	else if (data->rays[i].collision_y % 20 == 19 && data->rays[i].collision_x % 20 != 19)
	{
		data->rays[i].texture_x = (data->rays[i].collision_x % 20);
		if (data->rays[i].compass > 0 && data->rays[i].compass < 3.15)
			return (SOUTH);
		else
			return (NORTH);
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

	i = -1;
	while (data->rays[++i].length)
	{
		data->rays[i].orient = get_texture_orientation(data, i);
		if (i == 0)
			printf("intX: %i, intY %i, tX: %i\n", data->rays[i].collision_x, data->rays[i].collision_y, data->rays[i].texture_x);
	}
}
