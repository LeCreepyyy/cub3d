/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/28 15:46:47 by vpoirot          ###   ########.fr       */
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

typedef struct s_data
{
	char	**textures;
	char	**map_flat;
	int		*player_pos;
}	t_data;

int		tab_len(char **tab);
void	free_tab(char **tab);
int		ft_strlen(char *str);
void	print_tab(char **tab);
char	*get_next_line(int fd);
void	ft_exit(char *err, int code);
int		ft_printf(const char *str, ...);
void	parsing(char *map_path, t_data *data);
void	parse_map(char **ftab, int y, t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
