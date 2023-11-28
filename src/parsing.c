/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:13:15 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/28 15:40:56 by vpoirot          ###   ########.fr       */
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

void	checkrgb(char *line)
{
	// int	i;
	// int	rgb;

	// i = 0;
	// while (line[i] != NULL)
	// 	;
	(void)line;
}

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
			len++;
		}
	}
	if (ftab[y++] == NULL)
		ft_exit("Missing information", EXIT_FAILURE);
	parse_map(ftab, 10, data);
}

void	parsing(char *map_path, t_data *data)
{
	char	**ftab;

	if (ft_strncmp(&map_path[ft_strlen(map_path) - 4], ".cub", 4) != 0)
		ft_exit("Invalid extention", EXIT_FAILURE);
	ftab = file_to_tab(map_path);
	// print_tab(ftab);
	checkmap(ftab, data);
	// transform to 3 char**
	free_tab(ftab);
}
