/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 16:25:56 by bgaertne         ###   ########.fr       */
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
	setup_mlx(&data);
	ft_exit(NULL, EXIT_SUCCESS);
}
