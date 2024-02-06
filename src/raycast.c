/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/06 10:54:09 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * xy[0] = X value & xy[1] = Y value
*/
void	raygun(t_data *data, double x1, double y1, t_dda *ft_dda)
{
	double	delta_x;
	double	delta_y;
	double	max_delta;
	double	xy[2];
	double	t;

	dda(data, x1, y1, ft_dda);
	delta_x = ft_dda->collision_point[0] - x1;
	delta_y = ft_dda->collision_point[1] - y1;
	if (fabs(delta_x) > fabs(delta_y))
		max_delta = fabs(delta_x);
	else
		max_delta = fabs(delta_y);
	t = 0.0;
	while (t <= 1.0)
	{
		xy[0] = x1 + t * delta_x;
		xy[1] = y1 + t * delta_y;
		mlx_put_pixel(data->imgs.mp_ray, xy[0] * MP_WALL, xy[1] * MP_WALL,
			stack_pixel(&data->colors.yellow, NULL));
		t += 1.0 / max_delta;
	}
}

void	pewpewpew(t_data *data)
{
	t_dda	ft_dda;
	int		pixel_x;
	int		i;

	pixel_x = WIDTH;
	ft_dda.n = -1;
	i = 0;
	ft_dda.dir_x = data->player.dir_x;
	ft_dda.dir_y = data->player.dir_y;
	while (--pixel_x > 0)
	{	
		ft_dda.n++;
		ft_dda.camera_x = 2 * pixel_x / (double)WIDTH - 1;
		ft_dda.dir_x = data->player.dir_x + data->player.plane_x * ft_dda.camera_x;
		ft_dda.dir_y = data->player.dir_y + data->player.plane_y * ft_dda.camera_x;
		raygun(data, data->player.pos_x, data->player.pos_y, &ft_dda);
		//draw(data, &ft_dda, i++);
		draw_wall(data, &ft_dda, i++);
		free(ft_dda.collision_point);
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
	pass = 1;
}
