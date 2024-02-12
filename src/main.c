/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/12 11:18:30 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Data initialization.
 * @param data Data struct
 */
void	init_data(t_data *data)
{
	data->map_flat = NULL;
	data->textures = ft_calloc(sizeof(char *), 7);
	if (data->textures == NULL)
		ft_exit("malloc", EXIT_FAILURE);
	data->player_pos = malloc(sizeof(int) * 3);
	data->player_pos[0] = 0;
	data->player_pos[1] = 0;
	data->player_pos[2] = 0;
	data->imgs.wall_north = NULL;
	data->imgs.wall_south = NULL;
	data->imgs.wall_east = NULL;
	data->imgs.wall_west = NULL;
	data->imgs.mp_wc = 0;
	data->imgs.mp_player = NULL;
	data->imgs.mp_wall = NULL;
	data->imgs.mpfc = 0;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->imgs.wall_resolution = 0;
	init_colors(data);
}

/**
 * Prints an error message and exit the program with a given code.
 * @param err Error message to print.
 * @param code Exit code of the program.
 */
void	ft_exit(char *err, int code)
{
	if (err != NULL)
		ft_printf("Error\n%s\n", err);
	exit(code);
}

/**
 * Cub3d, by vpoirot & bgaertne.
 * @param argc main-given number of arguments.
 * @param argv main-given array of arguments.
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_exit("Missing arg", EXIT_FAILURE);
	init_data(&data);
	parsing(argv[1], &data);
	if (data.player_pos[0] == 0 || data.player_pos[1] == 0
		|| data.player_pos[2] == 0)
		ft_exit("Missing player info", EXIT_FAILURE);
	setup_mlx(&data);
	ft_exit(NULL, EXIT_SUCCESS);
}

int	is_different(char c, char *charlist)
{
	int	i;

	i = -1;
	while (charlist[++i])
		if (charlist[i] == c)
			return (0);
	return (1);
}

int	check_forbidden_char(char *input, char *excludes)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_different(input[i], excludes))
			return (1);
		i++;
	}
	return (0);
}
