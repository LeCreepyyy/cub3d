/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/08 10:53:30 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	graphics(t_data *data)
{
	int				i;
	long long int	distance;

	i = -1;
	while (++i < WIDTH)
	{
		if (i == 0)
			distance = sqrt(pow(data->rays[i], 2) - pow(i, 2));
		else
			distance = data->rays[i];
		if (i == 0)
			printf("0, %lld\n", distance);
		if (i == 839)
			printf("839, %lld\n", distance);
		if (i == 1679)
			printf("1679, %lld\n", distance);
	}
}