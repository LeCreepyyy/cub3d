/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:43 by vpoirot           #+#    #+#             */
/*   Updated: 2023/12/20 10:42:57 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (len < 100)
	{
		mlx_put_pixel(data->imgs.mp_ray, data->imgs.mp_player->instances[0].x, data->imgs.mp_player->instances[0].y, 0x08);
		// mlx_put_pixel(data->imgs.mp_ray, round(pos_x), round(pos_y), 0x08);
		// mlx_put_pixel(data->imgs.mp_ray, round(pos_x) + 1, round(pos_y), 0x08);
		// mlx_put_pixel(data->imgs.mp_ray, round(pos_x) + 2, round(pos_y), 0x08);
		pos_x += dir_x;
		pos_y += dir_y;
		len++;
	}
	return (len);
}
