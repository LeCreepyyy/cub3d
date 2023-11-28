/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/28 19:14:44 by bgaertne         ###   ########.fr       */
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

int		tab_len(char **tab);
void	free_tab(char **tab);
void	print_tab(char **tab);
void	ft_exit(char *err, int code);
void	parsing(char *map_path, t_data *data);
void	parse_map(char **ftab, int y, t_data *data);

#endif
