/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:40 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/25 15:13:08 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_value_dda_y(t_dda *dda)
{
	if (dda->dir_y != 0)
		dda->delta_dist_y = fabs(1 / dda->dir_y);
	else
		dda->delta_dist_y = INFINITY;
	if (dda->dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = 0;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = dda->delta_dist_y;
	}
}

void	define_value_dda(t_dda *dda)
{
	if (dda->dir_x != 0)
		dda->delta_dist_x = fabs(1 / dda->dir_x);
	else
		dda->delta_dist_x = INFINITY;
	if (dda->dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = 0;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = dda->delta_dist_x;
	}
	define_value_dda_y(dda);
}

double	*dda(t_data *data, double start_x, double start_y, t_dda *dda)
{
	dda->collision_point = malloc(2 * sizeof(double));
	dda->ray_x = start_x;
	dda->ray_y = start_y;
	define_value_dda(dda);
	while (1)
	{
		if (data->map_flat[(int)dda->ray_y / MP_WALL]
			[(int)dda->ray_x / MP_WALL] == '1')
			break ;
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->ray_x += dda->step_x;
			dda->collision_axis = 'x';
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->ray_y += dda->step_y;
			dda->collision_axis = 'y';
		}
	}
	dda->collision_point[0] = dda->ray_x;
	dda->collision_point[1] = dda->ray_y;
	return (dda->collision_point);
}

// double *dda(t_data *data, double start_x, double start_y, t_dda *dda)
// {
// 	dda->collision_point = malloc(2 * sizeof(double));
// 	dda->ray_x = (int)start_x;
// 	dda->ray_y = (int)start_y;
// 	if (dda->dir_x != 0)
// 		dda->delta_dist_x = fabs(1 / dda->dir_x);
// 	else
// 		dda->delta_dist_x = INFINITY;
// 	if (dda->dir_y != 0)
// 		dda->delta_dist_y = fabs(1 / dda->dir_y);
// 	else
// 		dda->delta_dist_y = INFINITY;
// 	if (dda->dir_x < 0)
// 	{
// 		dda->step_x = -1;
// 		dda->side_dist_x = (start_x - dda->ray_x) * dda->delta_dist_x;
// 	}
// 	else
// 	{
// 		dda->step_x = 1;
// 		dda->side_dist_x = (dda->ray_x + 1.0 - start_x) * dda->delta_dist_x;
// 	}
// 	if (dda->dir_y < 0)
// 	{
// 		dda->step_y = -1;
// 		dda->side_dist_y = (start_y - dda->ray_y) * dda->delta_dist_y;
// 	}
// 	else
// 	{
// 		dda->step_y = 1;
// 		dda->side_dist_y = (dda->ray_y + 1.0 - start_y) * dda->delta_dist_y;
// 	}
// 	while (1)
// 	{
// 		if (data->map_flat[dda->ray_y / MP_WALL][dda->ray_x / MP_WALL] == '1')
// 			break ;
// 		if (dda->side_dist_x < dda->side_dist_y)
// 		{
// 			dda->side_dist_x += dda->delta_dist_x;
// 			dda->ray_x += dda->step_x;
// 		}
// 		else
// 		{
// 			dda->side_dist_y += dda->delta_dist_y;
// 			dda->ray_y += dda->step_y;
// 		}
// 	}
// 	dda->collision_point[0] = dda->ray_x;
// 	dda->collision_point[1] = dda->ray_y;
// 	return (dda->collision_point);
// }
