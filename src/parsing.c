/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:13:15 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/12 12:51:28 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Calculates the number of line in file
 * @param path Path of map file
 * @return Number of line in file
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
 * Stores file content into a char** representing the game's map.
 * @param path Path of map file
 * @return char** representing the game's map.
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

/**
 * RGB checking.
 * @param line Input to check
 */
void	checkrgb(char *line)
{
	int		i;
	char	**rgb;

	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(&line[i], ',');
	i = -1;
	while (rgb[++i] != NULL)
		if ((ft_strlen(rgb[i]) > 3 || !ft_strncmp(rgb[i], "\n", 1)
				|| ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			&& check_forbidden_char(rgb[i], "0123456789\n"))
			ft_exit("RGB false", EXIT_FAILURE);
	free_tab(rgb);
}

/**
 * Checks for map, textures and rgb validity.
 * @param ftab char** containing the map.
 * @param data Data struct.
 */
void	checkmap(char **ftab, t_data *data)
{
	int		y;
	int		len;

	y = -1;
	len = 0;
	while (ftab[++y] != NULL && len != 6)
	{
		if (ft_strncmp(ftab[y], "NO", 2) == 0
			|| ft_strncmp(ftab[y], "SO", 2) == 0
			|| ft_strncmp(ftab[y], "WE", 2) == 0
			|| ft_strncmp(ftab[y], "EA", 2) == 0
			|| ftab[y][0] == 'F' || ftab[y][0] == 'C')
		{
			if (ftab[y][0] == 'F' || ftab[y][0] == 'C')
				checkrgb(ftab[y]);
			else if (ft_strncmp(&ftab[y][ft_strlen(ftab[y]) - 5]
				, ".png", 4) != 0)
				ft_exit("Given image's format is not valid", EXIT_FAILURE);
			data->textures[len] = ft_strdup(ftab[y]);
			len++;
		}
	}
	y = skip_empty_lines(ftab, y);
	parse_map(ftab, y, data);
	store_map(ftab, y, data);
}

/**
 * Main parsing function.
 * @param map_path Path of the map file to be parsed.
 * @param data Data struct.
 */
void	parsing(char *map_path, t_data *data)
{
	char	**ftab;

	if (ft_strncmp(&map_path[ft_strlen(map_path) - 4], ".cub", 4) != 0)
		ft_exit("Invalid extention", EXIT_FAILURE);
	ftab = file_to_tab(map_path);
	checkmap(ftab, data);
	free_tab(ftab);
}
