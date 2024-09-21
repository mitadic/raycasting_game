/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:59:22 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/20 18:36:17 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fcntl.h not found on 42berlin computers, found a workaround*/

#ifndef CUB3D_H
# define CUB3D_H

// Settings
# define SCREEN_W 512
# define SCREEN_H 384
# define PLAY_FPS 30

# define LEGAL_CHARS " 10NESW"
# define PLAYER_DIR "NESW"
# define M_PI           3.14159265358979323846  /* pi */
# define BOGENMASS 1.047
# define FOV (M_PI / 3)
# define ENDLINE 1

# define HORIZONTAL 100
# define VERTICAL 200

# define WALL_N 0
# define WALL_E 1
# define WALL_S 2
# define WALL_W 3

# define MICROSEC_PER_S 1000000
# define MAX_FPS 120

// scale up the speeds as PLAY_FPS is set lower
# define ROT_SPEED 0.015 * MAX_FPS / PLAY_FPS
# define MOV_SPEED 0.0125 * MAX_FPS / PLAY_FPS

# define BLACK	0x000000
# define WHITE	0xFFFFFF
# define RED	0xFF0000
# define GREEN	0x00FF00
# define BLUE	0x0000FF
# define YELLOW	0xFAEE05
# define ORANGE 0xBA8507

// Linux key codes
#define KEY_ESC		65307
#define KEY_W		119
#define KEY_A		97
#define KEY_S		115
#define KEY_D		100
#define KEY_LEFT	65361
#define KEY_RIGHT	65363

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "errors.h"

/*Map file analysis information and internal ds storage*/
typedef struct s_map
{
	int		max_x;
	int		max_y;
	char	**vals;
} t_map;

/* Key statuses (0 or 1) */
typedef struct s_key_state
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_key_state;

/* Player position expressed as a 2D vector */
typedef struct s_pl_pos
{
	float		x;
	float		y;
	char		direction;
	float		player_angle_degree;
	float		player_angle_radian;
}	t_pl_pos;

/* Rays, will need (screen width) number of those */
typedef struct s_rays
{
	float	dir_x;
	float	dir_y;
	float	ray_angle;
	float 	deltaDist_X;
	float	deltaDist_Y;
	float	sideDist_X;
	float	sideDist_Y;
	float 	distance;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	float	wall_height;
	char	wall_to_the;
	int		side;
	float	intermediate_hit_x;
	float	intermediate_hit_y;
	float	hit_x;
	float	hit_y;
}	t_rays;

/*
All of these are initialized by MiniLibX suite functions, not manually:
-endian
	is about how data is stored within say 32bits, so RGBA or ARGB or otherwise
-line_length (== "scanline")
	is the total number of bytes need to represent a row of pixels
-bits_per_pixel;
	determines how many bytes each "pixel" is taking up
*/
typedef struct s_img_buff
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_buff;

typedef struct s_fps
{
	struct timeval	last_render;
}	t_fps;

typedef struct s_text
{
	void	*img;
	int		size_x;
	int		size_y;
}	t_text;

/* Encapsulating other structs as abstractions / groups
	though map->vals will need malloc, map itself needs not be a pointer */
typedef struct s_data
{
	t_map		
	map;
	t_pl_pos	pl_pos;
	t_key_state	key_state;
	t_rays		*rays;
	void		*mlx;
	void		*win;
	t_img_buff	img_buff;
	t_fps		time;
	t_text		txt[4];
}	t_data;


// A
// init.c
int		init(t_data *data, char *map_filename);

// B
// map_parsing_control.c
int		validate_map(t_data *data, char *map_filename);
// map_parsing_flood_fill.c
int		flood_fill(t_data *data);
void	free_map_copy(char **map_copy, int columns_allocated);
// map_parsing_flood_sim.c
int		flood_simulation(t_data *data, char **map_copy);

// C
// raycasting.c
int math(t_data *data);

//raycasting2.c
void calculate_hit_point(t_rays *ray, t_pl_pos player);
void calculate_wall_height(t_rays *ray);
void assign_wall_color(t_rays *ray);

// helper_functions.c
float ft_abs(float number);
// map.c
char **generate_bogus_map(void);

// D
// go_mlxing.c
void	go_mlxing(t_data *data);
// player_movements.c
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

// E
// draw_columns.c
void	draw_columns(t_data *data);

// Z
// failure_management.c
/*
	- error() usage:
		return(error(err_msg, passthrough_return_value));
	- bail() typedef struct s_rays

usage:
		pass the data to free and the exit code. It will exit();
	- error_and_bail() usage:
		pass the data to free, the msg to print, the exit code. It will exit();

In summary:
	- error() prints and returns, doesn't free
	- bail() frees and exits
	- error_and_bail() prints, frees and exits
*/
int		error(char* err_msg, int return_value);
void    bail(t_data *data, int exit_status);
void	error_and_bail(t_data *data, char *err_msg, int exit_status);

// freeing_protocol.c
void	purge(t_data *data);
void handle_sigint(int sig);

#endif
