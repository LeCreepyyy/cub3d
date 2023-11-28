/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:20:42 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/28 11:36:56 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(char **ftab, int y, t_map *s_map)
{
	int	x;
	int	isin;

	x = -1;
	(void)s_map;
	while (ftab[y] != NULL && (ftab[y][++x] != '\n' || ftab[y][++x] != 0))
		if (ftab[y][x] != ' ' && ftab[y][x] != '1')
			ft_exit(":File content invalid", EXIT_FAILURE);
	isin = 0;
	while (ftab[++y] != NULL && y != tab_len(ftab) - 1)
	{
		x = 0;
		while (ftab[y][x] == ' ' || ftab[y][x] == '\t')
			x++;
		if (ftab[y][x] != '1')
			ft_exit("File content invalid", EXIT_FAILURE);
		while (ftab[y][x] != '\n' && ftab[y][x] != 0)
		{
			if (ftab[y][x] == ' ' && ((ftab[y -1][x] != '1'
				&& ftab[y -1][x] != ' ') || (ftab[y +1][x] != '1'
				&& ftab[y +1][x] != ' ') || (ftab[y][x -1] != '1'
				&& ftab[y][x -1] != ' ') || (ftab[y][x +1] != '1'
				&& ftab[y][x +1] != ' ')))
				ft_exit("Map invalid", EXIT_FAILURE);
			else if (ftab[y][x] != '1' && ftab[y][x] != '0' && ftab[y][x] != 'N'
				&& ftab[y][x] != 'S' && ftab[y][x] != 'W' && ftab[y][x] != 'E'
				&& ftab[y][x] != ' ')
				ft_exit("Map content invalid", EXIT_FAILURE);
			if (isin == 0 && (ftab[y][x] == 'S' || ftab[y][x] == 'W'
				|| ftab[y][x] == 'E' || ftab[y][x] == 'N'))
				isin = 1;
			else if (isin == 1 && (ftab[y][x] == 'S' || ftab[y][x] == 'W'
				|| ftab[y][x] == 'E' || ftab[y][x] == 'N'))
				ft_exit("too many starting point", EXIT_FAILURE);
			x++;
		}
	}
	x = -1;
	while (ftab[y] != NULL && ftab[y][++x] != '\n' && ftab[y][++x] != 0)
		if (ftab[y][x] != ' ' && ftab[y][x] != '1')
			ft_exit("File content invalid", EXIT_FAILURE);
}
