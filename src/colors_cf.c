/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_cf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:02:00 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/08 11:47:11 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
