/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/03 13:30:01 by bgaertne         ###   ########.fr       */
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

void	draw_wall(t_data *data, t_dda *dda, int pixel_x)
{
	int	pixel_y;
	int	wall_end;
	int	wall_start;
	int	line_height;

	line_height = (int)(HEIGHT / dda->wall_dist);
	wall_start = (-line_height + HEIGHT) / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = (line_height + HEIGHT) / 2;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	pixel_y = -1;
	while (++pixel_y < wall_start)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.ceilling, NULL));
	while (++pixel_y < wall_end)
	{
		if (dda->side == 0)
		{
			if (dda->dir_x > 0)
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.green, NULL));
			else
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.lime, NULL));
		}
		else
		{
			if (dda->dir_y > 0)
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.red, NULL));
			else
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.orange, NULL));
		}
	}
	while (++pixel_y < HEIGHT)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.floor, NULL));
}

/**
 * Draws wall arround a given center point.
 * @param data Structure Data
 * @param wall_height Hauteur de mur a dessiner (en pixel).
 * @param map_x coordonnees X du point de depart du mur sur la fenetre.
 * @param map_y Coordonnees Y du point de depart du mur sur la fenetre.
 */
// void	draw_wall(t_data *data, int i, int map_x, int map_y)
// {
// 	int	l;
// 	int	j;
// 	int	k;
// 	uint32_t color;

// 	l = -1;
// 	j = 1;
// 	k = 0;
// 	color = stack_pixel(&data->colors.black, NULL);
// 	if (data->rays[i].orient == NORTH)
// 		color = stack_pixel(&data->colors.red, NULL);
// 	if (data->rays[i].orient == SOUTH)
// 		color = stack_pixel(&data->colors.orange, NULL);
// 	if (data->rays[i].orient == EAST)
// 		color = stack_pixel(&data->colors.green, NULL);
// 	if (data->rays[i].orient == WEST)
// 		color = stack_pixel(&data->colors.lime, NULL);
// 	if (i > 498 && i < 502)
// 		color = stack_pixel(&data->colors.white, NULL);
// 	while (++l < data->rays[i].wall_height)
// 	{
// 		if (l > (data->rays[i].wall_height / 2))
// 			mlx_put_pixel(data->imgs.graph, map_x, map_y + j++, color);
// 		else
// 			mlx_put_pixel(data->imgs.graph, map_x, map_y - k++, color);
// 	}
// }







