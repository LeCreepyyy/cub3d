/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:01:31 by vpoirot           #+#    #+#             */
/*   Updated: 2024/02/06 14:06:03 by bgaertne         ###   ########.fr       */
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
# define MP_WALL 20

# define WIDTH 1680
# define HEIGHT 1024

# define NORTH 1
# define EAST 2
# define WEST 3
# define SOUTH 4

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
	struct s_rgba	white;
	struct s_rgba	black;
	struct s_rgba	green;
	struct s_rgba	lime;
	struct s_rgba	orange;
	struct s_rgba	red;
	struct s_rgba	yellow;
	struct s_rgba	dark_blue;
	struct s_rgba	light_blue;
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
	int				wall_resolution;
	mlx_image_t		*floor;
	mlx_image_t		*ceiling;
	mlx_image_t		*mp_player;
	mlx_image_t		*mp_wall;
	int				mp_wc;
	mlx_image_t		*mp_floor;
	int				mpfc;
	mlx_image_t		*mp_ray;
	mlx_image_t		*graph;
	mlx_texture_t	*flash_txtr;
	mlx_image_t		*flash;
	mlx_texture_t	*black_txtr;
	mlx_image_t		*black;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
};

typedef struct s_dda
{
	int		n;
	double	*collision_point;
	int		ray_x;
	int		ray_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		side;
	double	wall_dist;
}			t_dda;

typedef struct s_data
{
	char			**textures;
	char			**map_flat;
	int				*player_pos;
	mlx_t			*mlx_ptr;
	struct s_ray	*rays;
	struct s_img	imgs;
	struct s_colors	colors;
	struct s_player	player;
}					t_data;

// main.c		NORM_OK
void		init_data(t_data *data);
void		ft_exit(char *err, int code);
int			main(int argc, char **argv);

// tab_utils.c
char		*get_texture(char c, t_data *data);
int			tab_len(char **tab);
void		free_tab(char **tab);
void		print_tab(char **tab);

// parsing.c
int			file_len(char *path);
char		**file_to_tab(char *path);
void		checkrgb(char *line);
void		checkmap(char **ftab, t_data *data);
void		parsing(char *map_path, t_data *data);

// parsing_utils.c
int			skip_empty_lines(char **ftab, int y);
void		check(t_data *data, char **ftab, int y, int x);
void		parse_map(char **ftab, int y, t_data *data);
void		store_map(char **ftab, int y, t_data *data);

// setup_mlx.c
void		*px_memset(void *str, struct s_rgba color, size_t len);
void		setup_imgs(t_data *data);
void		setup_imgs2(t_data *data);
void		setup_mlx(t_data *data);

// minimap.c
void		minimap(t_data *data);
void		print_minimap_walls_and_floor(t_data *data, int x, int y);
void		print_minimap_player_and_rays(t_data *data);

// key_handler.c
int			is_wall(t_data *data, int y, int x);
void		ft_next_pos(t_data *data, double dir_x, double dir_y, double speed);
void		ft_rotate_point(double *dir_x, double *dir_y, double rotspeed);
int			pos_mouse(t_data *data);
void		ft_key_handler(t_data *data, double rotspeed, double speed);

// raycast.c
void		pewpewpew(t_data *data);
void		ray_view(t_data *data);
int			dtop(double position, int resolution);

// hooks.c		NORM_OK
void		ft_loop(void *param);
void		ft_loop2(t_data *data);
void		ft_flashlight(t_data *data);
void		action_flashlight(t_data *data, int code);

// graphics.c	NORM_VERIF
void		draw(t_data *data, t_dda *dda, int pixel_x);
uint32_t	stack_pixel(struct s_rgba *color, uint8_t *stack);
mlx_image_t	*get_texture_orientation(t_data *data, t_dda *dda);

// colors.c		NORM_OK
void		init_colors_cf(t_data *data);
void		init_color_cf2(t_data *data, char **res);
void		rgb_creator(struct s_rgba *color, uint8_t r, uint8_t g, uint8_t b);
void		init_colors(t_data *data);

// ft_dda.c		NORM_VERIF
double		*dda(t_data *data, double start_x, double start_y, t_dda *dda);
void		define_value_dda_y(t_dda *dda, double start_y);
void		define_value_dda_x(t_dda *dda, double start_x, double start_y);


#endif
