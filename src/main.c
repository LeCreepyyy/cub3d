/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:00:10 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/20 14:17:35 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(char *err, int code)
{
	if (err != NULL)
		ft_printf("Error\n%s\n", err);
	exit(code);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_exit("Missing arg", EXIT_FAILURE);
	parsing(argv[1]);
	ft_printf("Map ok\n");
	ft_exit(NULL, EXIT_SUCCESS);
}
