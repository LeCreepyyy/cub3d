/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/17 13:29:20 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

/*
wall_texture [0=NO, 1=SO, 2=WE, 3=EA]
top_ground [0=F, 1=C] f = ground / c = top
map_flat is same that so_long file
*/
typedef struct s_map
{
	char	**wall_texture;
	char	**top_ground;
	char	**map_flat;
}	t_map;

void	ft_exit(char *err, int code);
char	*get_next_line(int fd);
void	parsing(char *map_path);
int		ft_printf(const char *str, ...);

#endif
