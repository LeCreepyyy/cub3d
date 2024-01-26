/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/26 14:42:47 by bgaertne         ###   ########.fr       */
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
	data->imgs.floor = NULL;
	data->imgs.mp_wc = 0;
	data->imgs.ceiling = NULL;
	data->imgs.mp_player = NULL;
	data->imgs.mp_wall = NULL;
	data->imgs.mpfc = 0;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->rays = ft_calloc(sizeof(struct s_ray), WIDTH);
	init_colors(data);
}

void	rgb_creator(struct s_rgba *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
}


/**
 * Data initialization.
 * @param data Data struct
 */
void	init_colors(t_data *data)
{
	rgb_creator(&data->colors.red, 255, 0, 0);
	rgb_creator(&data->colors.orange, 255, 140, 0);
	rgb_creator(&data->colors.yellow, 255, 255, 0);
	rgb_creator(&data->colors.lime, 0, 255, 0);
	rgb_creator(&data->colors.green, 0, 140, 0);
	rgb_creator(&data->colors.dark_blue, 0, 0, 255);
	rgb_creator(&data->colors.light_blue, 0, 190, 255);
	rgb_creator(&data->colors.white, 255, 255, 255);
	data->colors.ceilling.a = 255;
	data->colors.floor.a = 255;
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
