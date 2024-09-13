/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:59:22 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/13 15:47:03 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fcntl.h not found on 42berlin computers, found a workaround*/

#ifndef CUB3D_H
# define CUB3D_H

# define FOV 60
# define BOGENMASS 1.047

# define LEGAL_CHARS " 10NESW"
# define PLAYER_DIR "NESW"
# define SCREEN_W 320
# define SCREEN_H 180
# define M_PI           3.14159265358979323846  /* pi */
# define ENDLINE 1

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "errors.h"

/*Map file analysis information and internal ds storage*/
typedef struct s_map
{
	int		max_x;
	int		max_y;
	char	**vals;
} t_map;

/* Player position expressed as a 2D vector */
typedef struct s_pl_pos
{
	float	x;
	float	y;
	char direction;
	float player_angle_degree;
	float player_angle_radian;

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
	float	side_delta_incr_X;
	float	side_delta_incr_Y;
	float 	distance;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	float	wall_height;
}	t_rays;

typedef struct s_img_buff
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_buff;

/* Encapsulating other structs as abstractions / groups
	though map->vals will need malloc, map itself needs not be a <t_map *map>
 */
typedef struct s_data
{
	t_map		map;
	t_pl_pos	pl_pos;
	t_rays		*rays;
	void		*mlx;
	void		*win;
	t_img_buff	img_buff;
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
// helper_functions.c
float ft_abs(float number);
// map.c
char **generate_bogus_map(void);

// D
// go_mlxing.c
void	go_mlxing(t_data *data);

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

#endif
