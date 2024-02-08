/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/08 14:09:22 by vpoirot          ###   ########.fr       */
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
			&img->pixels[((pixel_x * 4) + (((int)img->width * 4) * pixel_y))]));
}

/**
 * @param img Send North, South, East or West texture.
 * If orient = 1 is X axis. If orient = 2 is Y axis.
 * @return Good pixel for mlx_put_pixel.
*/
uint32_t	get_pixel_to_draw(mlx_image_t *img, t_dda *dda, int orient, int pixel_y)
{
	double	vecteur_x;

	if (orient == 1)
		vecteur_x = dda->collision_point[0] - (int)dda->collision_point[0];
	else
		vecteur_x = dda->collision_point[1] - (int)dda->collision_point[1];
	int		ligne_x = (int)round(img->width * vecteur_x);
	int		line_height = (int)(HEIGHT) / dda->wall_dist;
	int		ligne_y = img->height * pixel_y / line_height;
	return (code_pixel(img, ligne_x, ligne_y));
}

void	draw_img(t_data *data)
{
	int	x = WIDTH / 3;
	int	delta_width = data->imgs.wall_west_texture->width;
	int	i = 0;
	int	bx;
	int	by;

	bx = x;
	while (delta_width)
	{
		int y = HEIGHT / 3;
		by = y;
		int delta_height = data->imgs.wall_west_texture->height;
		while (delta_height)
		{
			mlx_put_pixel(data->imgs.graph, y, x, code_pixel(data->imgs.wall_north, x - bx, y - by));
			i++;
			y++;
			delta_height--;
		}
		x++;
		delta_width--;
	}
}

/**
 * GREEN  : WEST
 * LIME   : EAST
 * RED    : SOUTH
 * ORANGE : NORTH
*/
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
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, get_pixel_to_draw(data->imgs.wall_west, dda, 2, pixel_y));
			else
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, get_pixel_to_draw(data->imgs.wall_east, dda, 2, pixel_y));
		}
		else
		{
			if (dda->dir_y > 0)
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, get_pixel_to_draw(data->imgs.wall_south, dda, 1, pixel_y));
			else
				mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, get_pixel_to_draw(data->imgs.wall_north, dda, 1, pixel_y));
		}
	}
	while (++pixel_y < HEIGHT)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.floor, NULL));
	//draw_img(data);
}
