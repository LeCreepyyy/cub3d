/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/01 15:59:30 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Creer un uint32_t avec 4 uint_8t pour l'utiliser dans mlx_put_pixel() */
uint32_t	stack_pixel(struct s_rgba *color, uint8_t *stack)
{
	uint32_t	pixels;

	if (color != NULL)
		pixels = (uint32_t)color->r << 24 | (uint32_t)color->g << 16
			| (uint32_t)color->b << 8 | (uint32_t)color->a;
	else if (stack != NULL)
		pixels = (uint32_t)stack[0] << 24 | (uint32_t)stack[1] << 16
			| (uint32_t)stack[2] << 8 | (uint32_t)stack[3];
	return (pixels);
}

uint32_t	code_pixel(mlx_image_t *img, int pixel_x, int pixel_y)
{
	return (stack_pixel(NULL,
			&img->pixels[((pixel_x + (int)img->width) * pixel_y)]));
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
	int			delta_height;
	int			iy;
	uint32_t 	color;
	mlx_image_t	*texture;


	color = stack_pixel(&data->colors.black, NULL);
	if (data->rays[i].orient == NORTH)
		texture = data->imgs.wall_north;
	if (data->rays[i].orient == SOUTH)
		texture = data->imgs.wall_south;
	if (data->rays[i].orient == EAST)
		texture = data->imgs.wall_east;
	if (data->rays[i].orient == WEST)
		texture = data->imgs.wall_west;
	if (data->rays[i].orient > 0)
	{
		delta_height = texture->height;
		iy = 0;
		while (delta_height)
		{
			mlx_put_pixel(data->imgs.graph, map_x, map_y, code_pixel(texture, data->rays[i].chunk , iy));
			map_y++;
			iy += 4;
			delta_height--;
		}
	}
	else
	{
		delta_height = data->rays[i].wall_height;
		while (delta_height)
		{
			mlx_put_pixel(data->imgs.graph, map_x, map_y, color);
			map_y++;
			delta_height--;
		}
	}
}

void	draw_img(t_data *data)
{
	int y = HEIGHT / 3;
	int	x = WIDTH / 3;
	int	delta_width = data->imgs.wall_west_texture->width;
	int	ix = 17;
	int	iy = 0;

	while (delta_width)
	{
		mlx_put_pixel(data->imgs.graph, y, x, code_pixel(data->imgs.wall_north, ix, iy));
		x++;
		iy += 4;
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
			draw_wall(data, i, i + WIDTH / 2, (HEIGHT / 2 ) + (data->rays[i].wall_height / 2));
		}
		else
		{
			distance = cos((i - (WIDTH / 2)) * 0.0007) * data->rays[i].length;
			data->rays[i].wall_height = HEIGHT / (distance * 0.04);
			if (data->rays[i].wall_height > HEIGHT)
				data->rays[i].wall_height = HEIGHT - 1;
			draw_wall(data, i, (WIDTH / 2) + ((WIDTH / 2) - i), (HEIGHT / 2 ) + (data->rays[i].wall_height / 2));
		}
	}
}




