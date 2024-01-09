/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/09 15:29:41 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	graphics(t_data *data)
{
	int		i;
	double	distance;
	int		wall_height;

	i = -1;
	while (++i < WIDTH)
	{
		if (i < 840)
			distance = sin(90 - ((i * 0.0009) / PI)) * data->rays[i];
		else
			distance = sin(90 - (((i - 839) * 0.0009) / PI)) * data->rays[i];
		wall_height = HEIGHT - distance;
		if (i < 840)
		{
			draw_wall(data, wall_height);
		}
		(void)wall_height;
	}
}

void	draw_wall(t_data *data, int wall_height)
{
	int i;
	int x;
	int y;

	i = -1;
	while (++i > wall_height)
	{
		
	}
}
