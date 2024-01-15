/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/15 10:54:03 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_wall(t_data *data, int y, int x)
{
	if (data->map_flat[y / MP_WALL][x / MP_WALL] == '1'
		|| data->map_flat[y / MP_WALL][x / MP_WALL] == ' ')
		return (0);
	return (1);
}

/**
 * @param pos_x position X du point de depart
 * @param pos_y position Y du point de depart
 * @param dir_x position X de la direction dans laquelle le rayon se dirige
 * @param dir_y position Y de la direction dans laquelle le rayon se dirige
	
    - La fonction prend en compte la direction X et Y pour trouver le
      prochain point ou un pixel sera placer pour former le rayon final.
    - La fonction renvoie un int qui contient le nombre de pixel placer,
      donc la longueur du rayon en pixel.

 * @return renvois le nombre de pixel place pour tracer le rayon
*/
double	raygun(t_data *data, double pos_x, double pos_y, double dir_x, double dir_y)
{
	double	len;

	len = 0;
	while (ray_wall(data, round(pos_y + dir_y) + MP_PLAYER / 2, round(pos_x + dir_x) + MP_PLAYER / 2))
	{
		mlx_put_pixel(data->imgs.mp_ray, round(pos_x) + MP_PLAYER / 2, round(pos_y) + MP_PLAYER / 2, 1436719011);
		pos_x += dir_x;
		pos_y += dir_y;
		len = dir_x + dir_y;
		len++;
	}
	return (len);
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
		data->rays[index++] = raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
	}
	limit = -1;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	while (++limit < WIDTH / 2)
	{
		ft_rotate_point(&dir_x, &dir_y, -0.0009);
		data->rays[index++] = raygun(data, data->player.pos_x, data->player.pos_y, dir_x, dir_y);
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
	graphics(data);
	pass = 1;
}
