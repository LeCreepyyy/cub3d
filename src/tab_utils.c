/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:36:29 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 10:58:13 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture(char c, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->textures[i] != NULL)
	{
		if (c == data->textures[i][0])
		{
			j = 2;
			while (data->textures[i][j] == ' ')
				j++;
			return (ft_strdup(&data->textures[i][j]));
		}
		i++;
	}
	return (NULL);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s", tab[i]);
		i++;
	}
}
