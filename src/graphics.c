/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/31 23:40:08 by bgaertne         ###   ########.fr       */
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
	int	l;
	int	j;
	int	k;
	uint32_t color;

	l = -1;
	j = 1;
	k = 0;
	color = stack_pixel(&data->colors.black, NULL);
	if (data->rays[i].orient == NORTH)
		color = stack_pixel(&data->colors.red, NULL);
	if (data->rays[i].orient == SOUTH)
		color = stack_pixel(&data->colors.orange, NULL);
	if (data->rays[i].orient == EAST)
		color = stack_pixel(&data->colors.green, NULL);
	if (data->rays[i].orient == WEST)
		color = stack_pixel(&data->colors.lime, NULL);
	if (i > 498 && i < 502)
		color = stack_pixel(&data->colors.white, NULL);
	while (++l < data->rays[i].wall_height)
	{
		if (l > (data->rays[i].wall_height / 2))
			mlx_put_pixel(data->imgs.graph, map_x, map_y + j++, color);
		else
			mlx_put_pixel(data->imgs.graph, map_x, map_y - k++, color);
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
	int				prev_chunk;
	int				ray_wall_index;
	double			distance;

	i = -1;
	get_texture_strip(data);
	prev_chunk = -1;
	ray_wall_index = 0;
	while (++i < WIDTH)
	{
		if (data->rays[i].chunk != -1)
		{
			if (prev_chunk != -1 && prev_chunk > data->rays[i].chunk)
				ray_wall_index = 0;
			data->rays[i].wall_index = ray_wall_index;
			prev_chunk = data->rays[i].chunk;
			ray_wall_index++;
		}
		else
		{
			ray_wall_index = -1;
			data->rays[i].wall_index = ray_wall_index;
		}
		if (i == 500)
				printf("chunk: %i, wIndex: %i\n", data->rays[i].chunk, data->rays[i].wall_index);
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




