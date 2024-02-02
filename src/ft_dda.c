/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:40 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/02 11:42:59 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_value_dda_y(t_dda *dda, double start_y)
{
	if (dda->dir_y != 0)
		dda->delta_dist_y = fabs(1 / dda->dir_y);
	else
		dda->delta_dist_y = INFINITY;
	if (dda->dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (start_y - dda->ray_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->ray_y + 1.0 - start_y) * dda->delta_dist_y;
	}
}

void	define_value_dda(t_dda *dda, double start_x, double start_y)
{
	if (dda->dir_x != 0)
		dda->delta_dist_x = fabs(1 / dda->dir_x);
	else
		dda->delta_dist_x = INFINITY;
	if (dda->dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (start_x - dda->ray_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->ray_x + 1.0 - start_x) * dda->delta_dist_x;
	}
	define_value_dda_y(dda, start_y);
}

// ne pas malloc collision_point
double	*dda(t_data *data, double start_x, double start_y, t_dda *dda)
{
	dda->collision_point = malloc(2 * sizeof(double));
	dda->ray_x = (int)start_x;
	dda->ray_y = (int)start_y;
	define_value_dda(dda, start_x, start_y);
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->ray_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->ray_y += dda->step_y;
			dda->side = 1;
		}
		printf("here\n");
		if (data->map_flat[dda->ray_y]
			[dda->ray_x] == '1')
			break ;
		printf("here2\n");
	}
	if (dda->side == 0)
		dda->wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->wall_dist = (dda->side_dist_y - dda->delta_dist_y);
	dda->collision_point[0] = start_x + dda->dir_x * dda->wall_dist;
	dda->collision_point[1] = start_y + dda->dir_y * dda->wall_dist;
	return (dda->collision_point);
}
