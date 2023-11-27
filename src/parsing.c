/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:13:15 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/27 14:46:05 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate the number of line in file
 * @param path path of map file
 * @return number of line in file
*/
int	file_len(char *path)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Read map", EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (len);
}

/**
 * set file content in char**
 * @param path path of map file
 * @return file content in char**
*/
char	**file_to_tab(char *path)
{
	int		i;
	int		fd;
	int		len;
	char	**file;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Read map", EXIT_FAILURE);
	len = file_len(path);
	file = malloc((len + 1) * sizeof(char *));
	if (!file)
	{
		close(fd);
		ft_exit("Read map", EXIT_FAILURE);
	}
	i = -1;
	file[++i] = get_next_line(fd);
	while (file[i] != NULL && i < (len - 1))
		file[++i] = get_next_line(fd);
	file[++i] = NULL;
	return (file);
}

void	checkmap(char **ftab)
{
	int		y;
	int		x;
	int		isin;

	y = 0;
	while (ft_strncmp(ftab[y], "", 0))
		y++;
	x = y;
	ft_printf("%s\n", ftab[y]);
	if (x != (y - 4))
		ft_exit("Sa marche po", EXIT_FAILURE);
	x = -1;
	while (ft_strncmp(ftab[++y], "", 0))
		;
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
	if (ftab[y] == NULL)
		ft_exit("File content invalid", EXIT_FAILURE);
	x = -1;
	while (ftab[y] != NULL && ftab[y][++x] != '\n' && ftab[y][++x] != 0)
		if (ftab[y][x] != ' ' && ftab[y][x] != '1')
			ft_exit("File content invalid", EXIT_FAILURE);
}

void	parsing(char *map_path)
{
	char	**ftab;

	if (ft_strncmp(&map_path[ft_strlen(map_path) - 4], ".cub", 4) != 0)
		ft_exit("Invalid extention", EXIT_FAILURE);
	ftab = file_to_tab(map_path);
	// print_tab(ftab);
	checkmap(ftab);
	// transform to 3 char**
	free_tab(ftab);
}
