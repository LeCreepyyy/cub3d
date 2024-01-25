/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/25 11:01:35 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Creer un uint32_t avec 4 uint_8t pour l'utiliser dans mlx_put_pixel() */
uint32_t	stack_pixel(uint8_t *stack)
{
	uint8_t		value1;
	uint8_t		value2;
	uint8_t		value3;
	uint8_t		value4;
	uint32_t	pixels;

	value1 = stack[0];
	value2 = stack[1];
	value3 = stack[2];
	value4 = stack[3];
	pixels = (uint32_t)value1 << 24 | (uint32_t)value2 << 16
		| (uint32_t)value3 << 8 | (uint32_t)value4;
	return (pixels);
}

/**
 * Draws wall arround a given center point.
 * @param data Structure Data
 * @param wall_height Hauteur de mur a dessiner (en pixel).
 * @param map_x coordonnees X du point de depart du mur sur la fenetre.
 * @param map_y Coordonnees Y du point de depart du mur sur la fenetre.
 */
void	draw_wall(t_data *data, int i, int map_x, int map_y)
{
	int	l;
	int	j;
	int	k;
	uint32_t color;

	l = -1;
	j = 1;
	k = 0;
	if (data->rays[i].orient == NORTH)
		color = UINT_PURPLE;
	if (data->rays[i].orient == SOUTH)
		color = UINT_BLUE;
	if (data->rays[i].orient == EAST)
		color = UINT_BEIGE;
	if (data->rays[i].orient == WEST)
		color = UINT_ORANGE;
	if (i < 20)
		color = UINT_CYAN;
	//color = 255999999;
	while (++l < data->rays[i].wall_height)
	{
		if (l > (data->rays[i].wall_height / 2))
			mlx_put_pixel(data->imgs.graph, map_x, map_y + j++, color);
		else
			mlx_put_pixel(data->imgs.graph, map_x, map_y - k++, color);
		//printf("stripx: %f\n", data->rays[i].strip_x);
	}
}

/* TEST: fonction qui affiche une image pixel par pixel */
void	draw_img(t_data *data)
{
	int	x = WIDTH / 3;
	int	delta_width = data->imgs.wall_west_texture->width;
	int	i = 0;

	while (delta_width)
	{
		int y = HEIGHT / 3;
		int delta_height = data->imgs.wall_west_texture->height;
		while (delta_height)
		{
			mlx_put_pixel(data->imgs.graph, y, x, stack_pixel(&data->imgs.wall_west->pixels[i]));
			i += 4;
			y++;;
			delta_height--;
		}
		x++;
		delta_width--;
	}
}

/**
 * Calculates the wall-cam distance and the wall_height and uses it to draw the walls.
 * @param data Data struct
 */
void	graphics(t_data *data)
{
	int				i;
	double			distance;

	i = -1;
	get_texture_strip(data);
	while (++i < WIDTH)
	{
		if (i < WIDTH / 2)
		{
			distance = cos(i * 0.0007) * data->rays[i].length;
			data->rays[i].wall_height = HEIGHT / (distance * 0.04);
			if (data->rays[i].wall_height > HEIGHT)
				data->rays[i].wall_height = HEIGHT - 1;
			draw_wall(data, i, i + WIDTH / 2, HEIGHT / 2);
		}
		else
		{
			distance = cos((i - (WIDTH / 2)) * 0.0007) * data->rays[i].length;
			data->rays[i].wall_height = HEIGHT / (distance * 0.04);
			if (data->rays[i].wall_height > HEIGHT)
				data->rays[i].wall_height = HEIGHT - 1;
			draw_wall(data, i, (WIDTH / 2) + ((WIDTH / 2) - i), HEIGHT / 2);
		}
	}
}




