/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/18 14:45:56 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double *didier(t_data *data, double start_x, double start_y, double dir_x, double dir_y) {
	double* collision_point = malloc(2 * sizeof(double));
    double ray_x = start_x;
    double ray_y = start_y;
    int step_x = (dir_x < 0) ? -1 : 1;
    int step_y = (dir_y < 0) ? -1 : 1;
    double delta_dist_x = (dir_x != 0) ? fabs(1 / dir_x) : INFINITY;
    double delta_dist_y = (dir_y != 0) ? fabs(1 / dir_y) : INFINITY;
    double side_dist_x = (dir_x < 0) ? (start_x - ray_x) * delta_dist_x : (ray_x + 1.0 - start_x) * delta_dist_x;
    double side_dist_y = (dir_y < 0) ? (start_y - ray_y) * delta_dist_y : (ray_y + 1.0 - start_y) * delta_dist_y;
	while (1) {
		if (data->map_flat[(int)ray_y / MP_WALL][(int)ray_x / MP_WALL] == '1')
			break ;
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            ray_x += step_x;
        } else {
            side_dist_y += delta_dist_y;
            ray_y += step_y;
        }
    }
    collision_point[0] = ray_x;
    collision_point[1] = ray_y;
    return (collision_point);
}

double	raygun(t_data *data, double x1, double y1, double dir_x, double dir_y)
{
	double	*end_point = didier(data, x1, y1, dir_x, dir_y);
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
	double	dir_x;
	double	dir_y;
	int 	index;

	limit = -1;
	index = 0;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&dir_x, &dir_y, 0.0009);
		data->rays[index++] = raygun(data, data->player.pos_x + (MP_PLAYER / 2), data->player.pos_y + (MP_PLAYER / 2), dir_x, dir_y);
		//raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
	}
	limit = -1;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&dir_x, &dir_y, -0.0009);
		data->rays[index++] = raygun(data, data->player.pos_x + (MP_PLAYER / 2), data->player.pos_y + (MP_PLAYER / 2), dir_x, dir_y);
		//raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
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
	raygun(data, data->player.pos_x, data->player.pos_y, data->player.dir_x, data->player.dir_y);
	pewpewpew(data);
	graphics(data);
	pass = 1;
}
