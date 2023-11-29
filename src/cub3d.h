/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 12:37:19 by vpoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
//# include "../MLX42/include/MLX42/MLX42.h"
# include "../TheLibft/base/libft.h"
# include "../TheLibft/ft_printf/ft_printf.h"
# include "../TheLibft/get_next_line/get_next_line.h"

typedef struct s_data
{
	char	**textures;
	char	**map_flat;
	int		*player_pos;
}	t_data;

// main.c
void	ft_exit(char *err, int code);

// utils.c
void	print_tab(char **tab);
int		tab_len(char **tab);
void	free_tab(char **tab);
char	*get_texture(char c, t_data *data);

// parsing.c
void	parsing(char *map_path, t_data *data);

// parsing_utils.c
void	parse_map(char **ftab, int y, t_data *data);
void	store_map(char **ftab, int y, t_data *data);
int		skip_empty_lines(char **ftab, int y);

#endif
