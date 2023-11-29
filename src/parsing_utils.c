/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creepy <creepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:20:42 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 17:14:02 by creepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_empty_lines(char **ftab, int y)
{
	while (ftab[y] != NULL && ftab[y][0] == '\n')
		y++;
	if (ftab[y] == NULL)
		ft_exit("Missing information", EXIT_FAILURE);
	return (y);
}

void	check(t_data *data, char **ftab, int y, int x)
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
	if (ftab[y][x] == 'S' || ftab[y][x] == 'W'
		|| ftab[y][x] == 'E' || ftab[y][x] == 'N')
	{
		if (data->player_pos[0])
			ft_exit("too many starting point", EXIT_FAILURE);
		else
		{
			data->player_pos[0] = ftab[y][x];
			data->player_pos[1] = y;
			data->player_pos[2] = x;
		}
	}
}

void	parse_map(char **ftab, int y, t_data *data)
{
	int	x;

	x = -1;
	while (ftab[y] != NULL && (ftab[y][++x] != '\n' || ftab[y][++x] != 0))
		if (ftab[y][x] != ' ' && ftab[y][x] != '1')
			ft_exit("File content invalid", EXIT_FAILURE);
	while (ftab[++y] != NULL && y != tab_len(ftab) - 1)
	{
		x = 0;
		while (ftab[y][x] == ' ')
			x++;
		if (ftab[y][x] != '1')
			ft_exit("File content invalid", EXIT_FAILURE);
		while (ftab[y][x] != '\n' && ftab[y][x] != 0)
		{
			check(data, ftab, y, x);
			x++;
		}
	}
	x = -1;
	while (ftab[y] != NULL && ftab[y][++x] != '\n' && ftab[y][++x] != 0)
		if (ftab[y][x] != ' ' && ftab[y][x] != '1' && ftab[y][x] != '\n')
			ft_exit("File content invalid", EXIT_FAILURE);
}

void	store_map(char **ftab, int y, t_data *data)
{
	int	w;

	w = 0;
	while (ftab[y + w])
		w++;
	data->map_flat = ft_calloc(sizeof(char *), w + 1);
	w = -1;
	while (ftab[y])
		data->map_flat[++w] = ft_strdup(ftab[y++]);
}
