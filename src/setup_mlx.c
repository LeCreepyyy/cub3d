/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:32 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 15:18:28 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_square(int x, int y, mlx_image_t i, t_data *data)
// {
// 	data->img = mlx_new_image(data->mlx_ptr, MP_TILE, MP_TILE);
// 	ft_memset(data->img->pixels, 255, data->img->width * data->img->height * sizeof(int32_t));
// 	mlx_image_to_window(data->mlx_ptr, data->img, x, y);
// }

// void	minimap(t_data *data)
// {
// 	print_square(0, 0, NULL, data);
// 	print_square(MP_TILE, 0, NULL, data);
// }

void	setup_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init(1480, 1024, "cub3d", false);
	//minimap(data);
	mlx_loop(data->mlx_ptr);
}
