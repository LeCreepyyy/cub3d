/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:13:15 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/17 14:08:37 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**file_to_tab(char *path)
{
	int		i;
	int		fd;
	char	**file;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Read map", EXIT_FAILURE);
	file = malloc(sizeof(char *) * file_len(path) + 1);
	if (!file)
	{
		close(fd);
		ft_exit("Read map", EXIT_FAILURE);
	}
	i = -1;
	file[++i] = get_next_line(fd);
	while (file[i] != NULL)
		file[++i] = get_next_line(fd);
	return (file);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	parsing(char *map_path)
{
	char	**ftab;

	ftab = file_to_tab(map_path);
	print_tab(ftab);
}
