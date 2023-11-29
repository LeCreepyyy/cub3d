/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2023/11/29 16:41:37 by bgaertne         ###   ########.fr       */
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
# include "../TheLibft/base/libft.h"
# include "../TheLibft/ft_printf/ft_printf.h"
# include "../TheLibft/get_next_line/get_next_line.h"

# define MP_PLAYER 25
# define MP_WALL 50
# define TEXTURE_H 50
# define TEXTURE_W 50

# define WHITE 0xFFFFFF
# define ORANGE 0xFFA500

typedef struct s_img
{
	mlx_texture_t	*wall_north_texture;
	mlx_image_t		*wall_north;
	mlx_texture_t	*wall_south_texture;
	mlx_image_t		*wall_south;
	mlx_texture_t	*wall_east_texture;
	mlx_image_t		*wall_east;
	mlx_texture_t	*wall_west_texture;
	mlx_image_t		*wall_west;
	mlx_image_t		*floor;
	mlx_image_t		*ceiling;
	mlx_image_t		*mp_player;
	mlx_image_t		*mp_wall;
}	t_img;


typedef struct s_data
{
	char			**textures;
	char			**map_flat;
	int				*player_pos;
	mlx_t			*mlx_ptr;
	struct s_img	imgs;
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

// setup_mlx.c
void	setup_mlx(t_data *data);

#endif
