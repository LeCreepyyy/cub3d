/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/09 15:05:30 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	graphics(t_data *data)
{
	int		i;
	double	distance;

	i = -1;
	while (++i < WIDTH)
	{
		if (i < 840)
			distance = sin(90 - ((i * 0.0009) / PI)) * data->rays[i];
		else
			distance = sin(90 - (((i - 839) * 0.0009) / PI)) * data->rays[i];
		if (i == 0)
			printf("0, %f\n", distance);
		if (i == 839)
			printf("839, %f\n", distance);
		if (i == 1679)
			printf("1679, %f\n", distance);
	}
}
