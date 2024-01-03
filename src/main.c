/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/03 11:05:49 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->imgs.ceiling = NULL;
	data->imgs.mp_player = NULL;
	data->imgs.mp_wall = NULL;
	data->fov = 80;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	init_colors(data);
}

void	init_colors(t_data *data)
{
	data->colors.red.r = 164;
	data->colors.red.g = 36;
	data->colors.red.b = 36;
	data->colors.red.a = 255;
	data->colors.lime.r = 104;
	data->colors.lime.g = 255;
	data->colors.lime.b = 4;
	data->colors.lime.a = 255;
	data->colors.dark_blue.r = 16;
	data->colors.dark_blue.g = 52;
	data->colors.dark_blue.b = 166;
	data->colors.dark_blue.a = 255;
	data->colors.light_blue.r = 169;
	data->colors.light_blue.g = 234;
	data->colors.light_blue.b = 254;
	data->colors.light_blue.a = 255;
}

void	ft_exit(char *err, int code)
{
	if (err != NULL)
		ft_printf("Error\n%s\n", err);
	exit(code);
}

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
