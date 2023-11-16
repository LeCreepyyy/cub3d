/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/16 15:20:55 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(int code)
{
	exit(code);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\n[Missing arg]\n");
		exit(EXIT_FAILURE);
	}
	parsing(argv[1]);
	ft_printf("Map ok\n");
	ft_exit(EXIT_SUCCESS);
}
