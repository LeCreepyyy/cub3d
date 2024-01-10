/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:17:47 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/10 15:51:40 by bgaertne         ###   ########.fr       */
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

void	draw_img(t_data *data)
{
	mlx_image_to_window(data->mlx_ptr, data->imgs.wall_east, WIDTH/3, HEIGHT/3 - 64);
	int x = WIDTH / 3;
	int delta_width = data->imgs.wall_east_texture->width;
	int i = 0;
	while (delta_width)
	{
		int y = HEIGHT / 3;
		int delta_height = data->imgs.wall_east_texture->height;
		while (delta_height)
		{
			printf("%d\n", data->imgs.wall_east->pixels[i]);
			mlx_put_pixel(data->imgs.graph, x, y, data->imgs.wall_east->pixels[i]);
			// La couleur n'est pas bonne.
			//exit(0);
			i++;
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
	draw_img(data);
}




