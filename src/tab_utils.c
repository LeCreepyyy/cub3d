/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:36:29 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/19 11:53:27 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Looks for the textures associated with the character C
 * in the data->textures array.
 * 
 * @param c Character that represents a specific texture.
 * @param data Data struct.
 * @return Sting containg both C and the texture's path ("C /path-to-texture")
 */
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
			data->textures[i][ft_strlen(data->textures[i]) - 1] = 0;
			return (&data->textures[i][j]);
		}
		i++;
	}
	return (NULL);
}

/**
 * Returns the length of an array
 * @param tab Array
 * @return Length of the array
 */
int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * Frees an array
 * @param tab Array
 */
void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

/**
 * Prints data of array. Debug.
 * 
 * @param tab Array to print
 */
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
