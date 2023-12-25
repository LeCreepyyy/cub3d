/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creepy <creepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2023/12/25 14:21:29 by creepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	ray_wall(t_data *data, int y, int x)
{
	if (data->map_flat[y / MP_WALL][x / MP_WALL] == '1')
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
int	raygun(t_data *data, double pos_x, double pos_y, double dir_x, double dir_y)
{
	int	len;

	len = 0;
	// uint32_t color = ft_pixel(
	// 	rand() % 0xFF, // R
	// 	rand() % 0xFF, // G
	// 	rand() % 0xFF, // B
	// 	rand() % 0xFF  // A
	// );
	// printf("%d\n", color);
	while (ray_wall(data, pos_y + dir_y, pos_x + dir_x))
	{
		mlx_put_pixel(data->imgs.mp_ray, round(pos_x), round(pos_y), 1331897026);
		pos_x += dir_x;
		pos_y += dir_y;
		len++;
	}
	return (len);
}
