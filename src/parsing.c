/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:13:15 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/20 15:07:09 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
calculate the number of line in file
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
	printf("len : %d\n", len);
	return (len);
}

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
	file[i] = NULL;
	return (file);
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
/*
void	checkmap(char **ftab)
{
	int		i;
	char	**temp;

	i = -1;
	temp = {"NO", "SO", "WE", "EA", "", "F", "C"};
	while (ftab[++i] && i < 7)
	{
		if (ft_strncmp(ftab[i], temp[i], 2) != 0)
			ft_exit("File content invalid", EXIT_FAILURE);
	}
}*/

void	parsing(char *map_path)
{
	char	**ftab;

	if (ft_strncmp(&map_path[ft_strlen(map_path) - 4], ".cub", 4) != 0)
		ft_exit("Invalid extention", EXIT_FAILURE);
	ftab = file_to_tab(map_path);
	print_tab(ftab);
	//verif map
	//transform to 3 char**
	free_tab(ftab);
}
