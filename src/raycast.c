/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/05 14:26:52 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


/**
 * convert Double Position in Pixel Position (int)
*/
int	dtop(double position, int resolution)
{
	if (resolution == WIDTH)
		return ((int)(position * WIDTH));
	return ((int)(position * HEIGHT));
}

void	raygun(t_data *data, double x1, double y1, t_dda *ft_dda)
{
	dda(data, x1, y1, ft_dda);
	double	delta_x = ft_dda->collision_point[0] - x1;
	double	delta_y = ft_dda->collision_point[1] - y1;
	double	max_delta = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);
	double	t = 0.0;
	while (t <= 1.0)
	{
		double	x = x1 + t * delta_x;
		double	y = y1 + t * delta_y;
		mlx_put_pixel(data->imgs.mp_ray, x * MP_WALL, y * MP_WALL, stack_pixel(&data->colors.yellow, NULL));
		t += 1.0 / max_delta;
	}
}

void	pewpewpew(t_data *data)
{
	t_dda	ft_dda;
	int		pixel_x;
	int		i;

	pixel_x = WIDTH;
	i = 0;
	ft_dda.dir_x = data->player.dir_x;
	ft_dda.dir_y = data->player.dir_y;
	while (--pixel_x > 0)
	{
		ft_dda.camera_x = 2 * pixel_x / (double)WIDTH - 1;
		ft_dda.dir_x = data->player.dir_x + data->player.plane_x * ft_dda.camera_x;
		ft_dda.dir_y = data->player.dir_y + data->player.plane_y * ft_dda.camera_x;
		raygun(data, data->player.pos_x, data->player.pos_y, &ft_dda);
		free(ft_dda.collision_point);
		draw_wall(data, &ft_dda, i++);
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
