/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_cf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:02:00 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/16 14:09:19 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Stores the RGBA informations of Ceiling and Floor in data->color..
 * @param data Data struct
 * @param res String containing the informations to store away.
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
 * Norm child of init_color_cf()
 * @param data Data struct.
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
