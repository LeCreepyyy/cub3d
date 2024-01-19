/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/19 12:59:19 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	raygun(t_data *data, double x1, double y1, t_dda *ft_dda)
{
	double	*end_point = dda(data, x1, y1, ft_dda);
	double	delta_x = end_point[0] - x1;
	double	delta_y = end_point[1] - y1;
	double	max_delta = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);
	int pixel_count = 0;
	double	res = sqrt(pow(end_point[0] - x1, 2) + pow(end_point[1] - y1, 2));
	double	t = 0.0;
	while (t <= 1.0)
	{
		double	x = x1 + t * delta_x;
		double	y = y1 + t * delta_y;
		mlx_put_pixel(data->imgs.mp_ray, round(x), round(y), 1436719011);
		t += 1.0 / max_delta;
		pixel_count++;
	}
	free(end_point);
	return (res);
}

void	pewpewpew(t_data *data)
{
	int		limit;
	int		index;
	t_dda	ft_dda;

	limit = -1;
	index = 0;
	ft_dda.dir_x = data->player.dir_x;
	ft_dda.dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&ft_dda.dir_x, &ft_dda.dir_y, 0.0007);
		data->rays[index++] = raygun(data, data->player.pos_x + (MP_PLAYER / 2), data->player.pos_y + (MP_PLAYER / 2), &ft_dda);
	}
	limit = -1;
	ft_dda.dir_x = data->player.dir_x;
	ft_dda.dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&ft_dda.dir_x, &ft_dda.dir_y, -0.0007);
		data->rays[index++] = raygun(data, data->player.pos_x + (MP_PLAYER / 2), data->player.pos_y + (MP_PLAYER / 2), &ft_dda);
	}
}

void	ray_view(t_data *data)
{
	static int	pass = 0;

	if (pass == 1)
	{
		mlx_delete_image(data->mlx_ptr, data->imgs.graph);
		mlx_delete_image(data->mlx_ptr, data->imgs.mp_ray);
	}
	data->imgs.mp_ray = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->imgs.graph = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx_ptr, data->imgs.mp_ray, 0, 0);
	mlx_set_instance_depth(&data->imgs.mp_ray->instances[0], 4);
	mlx_image_to_window(data->mlx_ptr, data->imgs.graph, 0, 0);
	mlx_set_instance_depth(&data->imgs.graph->instances[0], 1);
	pewpewpew(data);
	graphics(data);
	pass = 1;
}
