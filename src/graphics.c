/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/07 16:28:48 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	graphics(t_data *data)
{
	int	i;
	float	distance;

	i = -1;
	while (++i < WIDTH)
	{
		if (pow(i, 2) > 0)
			distance = sqrt(pow(data->rays[i], 2) - pow(i, 2));
		else
			distance = data->rays[i];
		if (i == 0)
			printf("0, %f\n", distance);
		if (i == 839)
			printf("839, %f\n", distance);
		if (i == 1679)
			printf("1679, %f\n", distance);
	}
}