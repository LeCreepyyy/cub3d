/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/11 14:11:50 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, int wall_height, int map_x, int map_y)
{
	int i;
	int j;
	int k;

	i = -1;
	j = 1;
	k = 0;
	while (++i < wall_height)
	{
		if (i > (wall_height / 2))
			mlx_put_pixel(data->imgs.graph, map_x, map_y - j++, 2559999999);
		else
			mlx_put_pixel(data->imgs.graph, map_x, map_y + k++, 2559999999);
	}
}

uint32_t	stack_pixel(uint8_t *stack)
{
    uint8_t		value1 = stack[0];
    uint8_t		value2 = stack[1];
    uint8_t		value3 = stack[2];
    uint8_t		value4 = stack[3];
	uint32_t	pixels = (uint32_t)value1 << 24 | (uint32_t)value2 << 16 | (uint32_t)value3 << 8 | (uint32_t)value4;
	return (pixels);
}

void	draw_img(t_data *data)
{
	int x = WIDTH / 3;
	int delta_width = data->imgs.wall_west_texture->width;
	int i = 0;
	while (delta_width)
	{
		int y = HEIGHT / 3;
		int delta_height = data->imgs.wall_west_texture->height;
		while (delta_height)
		{
			mlx_put_pixel(data->imgs.graph, y, x, stack_pixel(&data->imgs.wall_west->pixels[i]));
			// La couleur n'est pas bonne.
			//exit(0);
			i += 4;
			y++;;
			delta_height--;
		}
		x++;
		delta_width--;
	}
}

void	graphics(t_data *data)
{
	int				i;
	double			distance;
	unsigned int	wall_height;

	i = -1;
	while (++i < WIDTH)
	{
		if (i < 840)
		{
			distance = sin(90 - ((i * 0.0009) / PI)) * data->rays[i];
			wall_height = HEIGHT / 2 - tan(45) * distance;
			draw_wall(data, wall_height, i + 840, HEIGHT / 2);
		}
		else
		{
			distance = sin(90 - (((i - (WIDTH / 2)) * 0.0009) / PI)) * data->rays[i];
			wall_height = HEIGHT / 2 - tan(45) * distance;
			draw_wall(data, wall_height, (WIDTH / 2) + ((WIDTH / 2) - i), HEIGHT / 2);
		}
	}
}




