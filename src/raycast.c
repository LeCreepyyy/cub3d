/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/16 15:28:40 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	ray_wall(t_data *data, double y, double x)
// {
// 	// int	value;

// 	// value = 0;
// 	// if (fmod(x, MP_WALL) == 0)
// 	// 	value = x;
// 	// else if (fmod(y, MP_WALL) == 0)
// 	// 	value = y;
// 	// if (value != 0)
// 	// 	;
// 	// return (1);
// 	if (data->map_flat[(int)round(y) / MP_WALL][(int)round(x) / MP_WALL] == '1'
// 		|| data->map_flat[(int)round(y) / MP_WALL][(int)round(x) / MP_WALL] == ' ')
// 		return (0);
// 	return (1);
// }

int	raygun(t_data *data, double pos_x, double pos_y, double dir_x, double dir_y)
{
	double	ray_x;
	double	ray_y;
	double	delta_dist_x = fabs(1 / dir_x);
	double	delta_dist_y = fabs(1 / dir_y);
	int		step_x;
	int		step_y;
	int		hit;
	int		map_height = tab_len(data->map_flat);
	int		map_width = ft_strlen(data->map_flat[0]);

	hit = 0;
	if (dir_x < 0)
	{
		step_x = -1;
		ray_x = (int)pos_x;
	}
	else
	{
		step_x = 1;
		ray_x = ceil(pos_x);
	}
	if (dir_y < 0)
	{
		step_y = -1;
		ray_y = (int)pos_y;
	}
	else
	{
		step_y = 1;
		ray_y = ceil(pos_y);
	}
	while (!hit)
	{
		if (delta_dist_x < delta_dist_y)
		{
			delta_dist_x += fabs(1 / dir_x);
			ray_x += step_x;
		}
		else
		{
			delta_dist_y += fabs(1 / dir_y);
			ray_y += step_y;
		}
		if ((int)ray_y >= 0 && (int)ray_y < map_height && (int)ray_x >= 0 && (int)ray_x < map_width)
		{
			if (data->map_flat[(int)ray_y][(int)ray_x] == 1)
				hit = 1;
		}
		else
			break ;
	}
	mlx_put_pixel(data->imgs.mp_ray, ray_x, ray_y, 1436719011);
	return (0);
}

void	pewpewpew(t_data *data)
{
	int		limit;
	double	dir_x;
	double	dir_y;
	//int 	index;

	limit = -1;
	//index = 0;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&dir_x, &dir_y, 0.0009);
		//data->rays[index++] = raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
		raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
	}
	limit = -1;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&dir_x, &dir_y, -0.0009);
		//data->rays[index++] = raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
		raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
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
	mlx_image_to_window(data->mlx_ptr, data->imgs.graph, 0, 0);
	pewpewpew(data);
	//graphics(data);
	pass = 1;
}
