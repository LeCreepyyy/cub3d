/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/28 15:49:50 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map_flat = NULL;
	data->textures = NULL;
	data->player_pos = malloc(sizeof(int) * 3);
	data->player_pos[0] = 0;
	data->player_pos[1] = 0;
	data->player_pos[2] = 0;
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
	ft_printf("Map ok\n");
	ft_exit(NULL, EXIT_SUCCESS);
}
