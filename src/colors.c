/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:02:00 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/06 13:47:32 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Stores the RGBA informations of Ceiling and Floor in data->colors.
 * @param data Data struct
 * @param res String containing the informations to store away.
 */
void	init_colors_cf(t_data *data)
{
	char	**res;

	if (data->textures[4][0] == 'F')
	{
		res = ft_split(&data->textures[4][1], ',');
		data->colors.floor.r = ft_atoi(res[0]);
		data->colors.floor.g = ft_atoi(res[1]);
		data->colors.floor.b = ft_atoi(res[2]);
		free_tab(res);
	}
	else if (data->textures[5][0] == 'F')
	{
		res = ft_split(&data->textures[5][1], ',');
		data->colors.floor.r = ft_atoi(res[0]);
		data->colors.floor.g = ft_atoi(res[1]);
		data->colors.floor.b = ft_atoi(res[2]);
		free_tab(res);
	}
	init_color_cf2(data, res);
}

/**
 * Norm child of init_color_cf()
 * @param data Data struct.
 */
void	init_color_cf2(t_data *data, char **res)
{
	if (data->textures[4][0] == 'C')
	{
		res = ft_split(&data->textures[4][1], ',');
		data->colors.ceilling.r = ft_atoi(res[0]);
		data->colors.ceilling.g = ft_atoi(res[1]);
		data->colors.ceilling.b = ft_atoi(res[2]);
		free_tab(res);
	}
	else if (data->textures[5][0] == 'C')
	{
		res = ft_split(&data->textures[5][1], ',');
		data->colors.ceilling.r = ft_atoi(res[0]);
		data->colors.ceilling.g = ft_atoi(res[1]);
		data->colors.ceilling.b = ft_atoi(res[2]);
		free_tab(res);
	}
}

/**
 * Data initialization for colors structures.
 * @param color Color structure to initialize.
 * @param r red parameter.
 * @param g green parameter.
 * @param b blue parameter.
 */
void	rgb_creator(struct s_rgba *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
}

/**
 * Data initialization for colors structures.
 * @param data Data struct
 */
void	init_colors(t_data *data)
{
	rgb_creator(&data->colors.red, 255, 0, 0);
	rgb_creator(&data->colors.orange, 255, 140, 0);
	rgb_creator(&data->colors.yellow, 255, 255, 0);
	rgb_creator(&data->colors.lime, 0, 255, 0);
	rgb_creator(&data->colors.green, 0, 140, 0);
	rgb_creator(&data->colors.dark_blue, 0, 0, 255);
	rgb_creator(&data->colors.light_blue, 0, 190, 255);
	rgb_creator(&data->colors.white, 255, 255, 255);
	rgb_creator(&data->colors.black, 0, 0, 0);
	data->colors.ceilling.a = 255;
	data->colors.floor.a = 255;
}
