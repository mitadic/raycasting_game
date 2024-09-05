/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:59:22 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/05 14:01:06 by mitadic          ###   ########.fr       */
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
# define SCREEN_H 240

# define ENDLINE 1

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
// # include <asm-generic/fcntl.h>
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
}	t_pl_pos;

/* Rays, will need (screen width) number of those */
typedef struct s_rays
{
	float	dir_x;
	float	dir_y;
}	t_rays;

/* Encapsulating other structs as abstractions / groups
	though map->vals will need malloc, map itself needs not be a <t_map *map>
 */
typedef struct s_data
{
	t_map		map;
	t_pl_pos	pl_pos;
	t_rays		*rays;
}	t_data;

// init.c
int		init(t_data *data, char *map_filename);

// map_parsing_control.c
int		validate_map(t_data *data, char *map_filename);

// map_parsing_flood_fill.c
int		flood_fill(t_data *data);
void	free_map_copy(char **map_copy, int columns_allocated);

// map_parsing_flood_sim.c
int		flood_simulation(t_data *data, char **map_copy);

// failure_management.c
/*
	- error() usage:
		return(error(err_msg, passthrough_return_value));
	- bail() usage:
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
