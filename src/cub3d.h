/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2024/01/09 14:36:16 by bgaertne         ###   ########.fr       */
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

# define MP_PLAYER 5
# define MP_WALL 15
# define TEXTURE_H 20
# define TEXTURE_W 20

# define WIDTH 1680
# define HEIGHT 1024

# define PI 3.141592653589793

struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
};

struct s_colors
{
	struct s_rgba	red;
	struct s_rgba	dark_blue;
	struct s_rgba	light_blue;
	struct s_rgba	lime;
	struct s_rgba	ceilling;
	struct s_rgba	floor;
};

struct s_img
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
	mlx_image_t		*mp_floor;
	mlx_image_t		*mp_ray;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
};

typedef struct s_data
{
	char			**textures;
	char			**map_flat;
	int				*player_pos;
	int				*rays;
	mlx_t			*mlx_ptr;
	struct s_img	imgs;
	struct s_colors	colors;
	struct s_player	player;
}					t_data;

// main.c
void	init_data(t_data *data);
void	init_colors(t_data *data);
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

// shift_handler.c
void	ft_shift_handle(t_data *data, double rotspeed, double speed);
void	ft_rotate_point(double *dir_x, double *dir_y, double rotspeed);
int		pos_mouse(t_data *data);

// raycast.c
int		raygun(t_data *data, double pos_x, double pos_y,
			double dir_x, double dir_y);
int		*ray_view(t_data *data);

// graphics.c
void	graphics(t_data *data);

// colors_cf.c
void	init_colors_cf(t_data *data);

#endif
