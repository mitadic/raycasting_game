/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:59:22 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/17 15:46:09 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fcntl.h not found on 42berlin computers, found a workaround*/

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "errors.h"

// Settings
# define SCREEN_W 800
# define SCREEN_H 600
# define PLAY_FPS 30

# ifdef BONUS
#  define BONUS_ENABLED 1
# else
#  define BONUS_ENABLED 0
# endif

# define LEGAL_CHARS " 10NESW"
# define PLAYER_DIRS "NESW"
# define WHITESPACES " \t\v\f\r"
# define M_PI           3.14159265358979323846  /* pi */
# define BOGENMASS 1.047
# define ENDLINE 1

# define HORIZONTAL 100
# define VERTICAL 200

# define WALL_N 0
# define WALL_E 1
# define WALL_S 2
# define WALL_W 3

# define MICROSEC_PER_S 1000000
# define MAX_FPS 120

// Linux key codes
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define SCROLL_UP   4
# define SCROLL_DOWN 5

//colors
# define WHITE 0x000000

/*Map file analysis information and internal ds storage*/
typedef struct s_map
{
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
	int		ceiling[3];
	int		floor[3];
	int		rgb_c;
	int		rgb_f;
	int		max_x;
	int		max_y;
	char	**vals;
}	t_map;

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
	float		buffered_x_left;
	float		buffered_x_right;
	float		buffered_y_up;
	float		buffered_y_down;
	int			map_x_left;
	int			map_x_right;
	int			map_y_up;
	int			map_y_down;
}	t_pl_pos;

/* Rays, will need (screen width) number of those */
typedef struct s_rays
{
	float	dir_x;
	float	dir_y;
	float	ray_angle;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	float	distance;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
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
	int		width;
	int		height;
}			t_img_buff;

typedef struct s_fps
{
	struct timeval	last_render;
}	t_fps;

/*
Struct for textures. To be loaded as 'images', alongside their size_x & size_y
-void *img
	needs to be (void *) for MLX reasons, but when cast to (t_img *) reveals
	its true nature and contents (def found in mlx_int.h):
	- char	*data - binary image pixel information
	- int	size_line - "scanline"
	- int	bpp - bits per pixel
	- int	width - pixel count along x for the image
	- int	height - pixel count along y for the image
	<<< the above is what mlx_xpm_file_to_image() returns >>>
- size_x: needed to be passed to mlx_xpm_file_to_image()
- size_y: needed to be passed to mlx_xpm_file_to_image()
*/
typedef struct s_text
{
	void	*img;
	int		size_x;
	int		size_y;
}	t_text;

/*bpp: bits per pixel*/
/*size_line: line size(number of bytes per row)*/
/*endian (0 for little endian, 1 for big endian)*/
typedef struct s_minimap
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	float	scale;
	int		player_mini_x;
	int		player_mini_y;
	int		minimap_max_w;
	int		minimap_max_h;
}	t_minimap;

typedef struct s_settings
{
	float	fov;
	float	rot_speed;
	float	mov_speed;
}	t_settings;

/* Encapsulating other structs as abstractions / groups
	though map->vals will need malloc, map itself needs not be a pointer */
typedef struct s_data
{
	t_map		map;
	t_pl_pos	pl_pos;
	t_key_state	key_state;
	t_rays		*rays;
	void		*mlx;
	void		*win;
	t_img_buff	img_buff;
	t_fps		time;
	t_text		txt[4];
	t_minimap	minimap;
	t_settings	settings;
}	t_data;

// A

// init.c

int		init(t_data *data, char *map_filename);

// init_nullify.c

void	init_nullify(t_data *data);

// set_max_vector_values.c

int		set_max_vector_values(t_data *data, char *map_filename);

// B

// dotcub_parsing_control.c

int		parse_dotcub(t_data *data, char *map_filename);

// dotcub_parsing_extraction_control.c

int		extract_dotcub_values(t_data *data, int fd);

// dotcub_parsing_extraction_utils.c

int		extract_chars_from_line(t_data *data, int y, char **line);
int		calculate_line_len_without_final_endline(char *line);

// dotcub_parsing_getsingle_txtrgb.c

int		extract_single_texture_or_rgb(t_data *data, char *line);

// dotcub_parsing_rgb.c

int		extract_rgb(t_data *data, char *line, char where);

// dotcub_parsing_txt.c

int		extract_texture(t_data *data, char *line, char where);

// dotcub_valinit_map.c

int		val_init_map(t_data *data);
void	print_map(t_data *data);

// dotcub_valinit_txtrgb.c

int		val_init_txtrgb(t_data *data);

// map_parsing_flood_fill.c

int		flood_fill(t_data *data);
void	free_map_copy(char **map_copy, int columns_allocated);

// map_parsing_flood_sim.c

int		flood_simulation(t_data *data, char **map_copy);

// utils.c

void	free_strarr(char **strarr);
int		get_strings_count(char **strarr);
int		get_char_count(char *str, char c);
int		atoi_cub3d_rgb(const char *nptr);
int		is_textures_and_rgbs_extr_complete(t_data *data);

// C

// raycasting.c

int		math(t_data *data);

//raycasting2.c

void	calculate_intermediate_hitpoint(t_rays *ray, t_pl_pos player);
void	calculate_wall_height(t_rays *ray);
void	assign_wall_color(t_rays *ray);
void	adjust_for_fisheye_effect(t_pl_pos player, t_rays *ray,
			float distance_without_correction);
void	raycasting_loop(t_rays *ray, t_pl_pos player, char **map);

//raycasting3.c

void	calculate_distance(t_rays *ray, t_pl_pos player, char **map);

// helper_functions.c

float	ft_abs(float number);

// map.c

char	**generate_bogus_map(void);

// D

// go_mlxing.c

void	go_mlxing(t_data *data);

//key_handling.c

int		handle_keypress(int keycode, void *param);
int		handle_keyrelease(int keycode, void *param);
int		close_x(t_data *data);

//bonus_minimap.c

void	initialize_minimap(t_data *data);
void	draw_minimap_on_image(t_data *data, t_minimap *minimap);

//bonus_minimap2.c

void	draw_square(t_minimap *minimap, int x, int y, int color);
void	put_pixel_to_image(t_minimap *minimap, int x, int y, int color);

//bonus_mouse_rotation.c

int		handle_mouse_scroll_up(int button, int x, int y, void *param);
int		handle_mouse_scroll_down(int button, int x, int y, void *param);

// player_movements.c

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

//player_movements2.c

void	rotate_right(t_data *data);
void	rotate_left(t_data *data);

// E

// draw_columns.c

void	draw_columns(t_data *data);

// utils.c

float	get_the_float_component_of_hitp(t_data *data, int x);

// Z

// failure_management.c
/*
	- error() usage:
		return(error(err_msg, passthrough_return_value));
	- bail() usage:
		pass the data to free and the exit code. It will exit();
	- error_and_bail() usage:
		pass the data to free, the msg to print, the exit code. It will exit();

In summary:
	- error() prints and returns KO / OK, doesn't free
	- bail() frees and exits
	- error_and_bail() prints, frees and exits
*/

void	put_err_msg(char *err_msg);
int		error(char *err_msg, int return_value);
void	bail(t_data *data, int exit_status);
void	error_and_bail(t_data *data, char *err_msg, int exit_status);

// freeing_protocol.c

void	purge(t_data *data);

#endif
