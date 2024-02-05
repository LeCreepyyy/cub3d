/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/02/05 20:20:28 by bgaertne         ###   ########.fr       */
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

mlx_image_t	*get_texture_orientation(t_data *data, t_dda *dda)
{
	if (dda->side == 0 && dda->dir_x > 0)
		return(data->imgs.wall_west);
	else if (dda->side == 0 && dda->dir_x <= 0)
		return(data->imgs.wall_east);
	else if (dda->side != 0 && dda->dir_y > 0)
		return(data->imgs.wall_north);
	else if (dda->side != 0 && dda->dir_y <= 0)
		return(data->imgs.wall_south);
	return (NULL);
}

void	draw(t_data *data, t_dda *dda, int pixel_x)
{
	int			pixel_y;
	int			wall_end;
	int			wall_start;
	int			line_height;
	int			i;
	int			texture_offset;
	mlx_image_t	*texture;
	
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
	//////
	texture = get_texture_orientation(data, dda);
	texture_offset = 0;
	if (dda->side == 0)
		texture_offset = (int)dda->collision_point[1] % data->imgs.wall_resolution;
	if (dda->side == 1)
		texture_offset = (int)dda->collision_point[0] % data->imgs.wall_resolution;
	if (dda->n == WIDTH/2) // Afficher les datas du rayon centre
		printf("offset: %i, x: %f, y: %f\n", texture_offset, dda->collision_point[0], dda->collision_point[1]);
	i = texture_offset * 4;
	while (texture->pixels[i] && ++pixel_y < wall_end)
	{
		if (dda->n == WIDTH/2) // Afficher du rayon centre en rouge
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.red, NULL));
		else
			mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(NULL, &texture->pixels[i]));
		i += data->imgs.wall_resolution * 4;
	}
	//////////
	while (++pixel_y < HEIGHT)
		mlx_put_pixel(data->imgs.graph, pixel_x, pixel_y, stack_pixel(&data->colors.floor, NULL));
}

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
			mlx_put_pixel(data->imgs.graph, y, x, stack_pixel(NULL, &data->imgs.wall_west->pixels[i]));
			i += 4;
			y++;;
			delta_height--;
		}
		x++;
		delta_width--;
	}
}