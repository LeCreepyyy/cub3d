/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/09 15:06:52 by bgaertne         ###   ########.fr       */
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
	}
}
