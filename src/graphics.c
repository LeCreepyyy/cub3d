/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/09 13:59:02 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Returns a uint_32, made from 4 uint_8t from either a struct *color,
 * or a uint8_t *stack. one shall be NULL when using the other.
 * @param color Color structur containing the rgba datas to create a uint32_t,
 * NULL if stack is not.
 * @param stack uint8_t poiter array of color data to create a unit32_t,
 * NULL if color us not.
 */
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

/**
 * Returns datas of an img's pixel.
 * @param img Image provinding data
 * @param pixel_x X position of the pixel on the image
 * @param pixel_y Y position of the pixel on the image
 */
uint32_t	code_pixel(mlx_image_t *img, int pixel_x, int pixel_y)
{
	return (stack_pixel(NULL,
			&img->pixels[((pixel_x * 4) + (((int)img->width * 4) * pixel_y))]));
}

/**
 * Returns the exact pixel to draw on a specific point.
 * @param img image proving data
 * @param dda dda struct of the current ray (so current wall line)
 * @param orient orientation of the current wall line (int)
 * @param pixel_y Y position of the pixel to draw (texture position)
 * @return Good pixel for mlx_put_pixel.
*/
uint32_t	get_pixel_to_draw(mlx_image_t *img, t_dda *dda,
	int orient, int pixel_y)
{
	double	vecteur_x;
	int		line_x;
	int		line_y;
	int		line_height;

	if (orient == 1)
		vecteur_x = dda->collision_point[0] - (int)dda->collision_point[0];
	else
		vecteur_x = dda->collision_point[1] - (int)dda->collision_point[1];
	line_x = (int)round(img->width * vecteur_x);
	line_height = (int)(HEIGHT) / dda->wall_dist;
	line_y = img->height * pixel_y / line_height;
	return (code_pixel(img, line_x, line_y));
}

/**
 * Function that draws a wall line (called for each ray)
 * @param data Data struct.
 * @param dda dda struct of the current ray
 * @param pixel_x X postion of the current wall_line
 */
void	draw_wall(t_data *data, t_dda *dda, int pixel_x)
{
	int	pixel_y;
	int	wall_end;
	int	wall_start;
	int	line_height;

	line_height = (int)(HEIGHT / dda->wall_dist);
	wall_start = (-line_height + HEIGHT) / 2;
	wall_end = (line_height + HEIGHT) / 2;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	pixel_y = -1;
	while (++pixel_y < wall_start)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
			stack_pixel(&data->colors.ceilling, NULL));
	while (++pixel_y < wall_end)
		draw_wall2(data, dda, pixel_x, pixel_y);
	while (++pixel_y < HEIGHT)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
			stack_pixel(&data->colors.floor, NULL));
}

/**
 * Norm child of draw_wall()
 * @param data Data struct.
 * @param dda dda struct of the current ray
 * @param pixel_x X postion of the current wall_line
 * @param pixel_y Y postition (index) of the pixel to draw
 */
void	draw_wall2(t_data *data, t_dda *dda, int pixel_x, int pixel_y)
{
	int	wall_start;

	wall_start = ((int)-(HEIGHT / dda->wall_dist) + HEIGHT) / 2;
	if (dda->side == 0)
	{
		if (dda->dir_x > 0)
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
				get_pixel_to_draw(data->imgs.wall_east, dda, 2,
					pixel_y - wall_start));
		else
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
				get_pixel_to_draw(data->imgs.wall_west, dda, 2,
					pixel_y - wall_start));
	}
	else
	{
		if (dda->dir_y > 0)
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
				get_pixel_to_draw(data->imgs.wall_south, dda, 1,
					pixel_y - wall_start));
		else
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y,
				get_pixel_to_draw(data->imgs.wall_north, dda, 1,
					pixel_y - wall_start));
	}
}
