/* fcntl.h not found on 42berlin computers, found a workaround*/

#ifndef CUB3D_H
# define CUB3D_H

# define FOV 60
# define BOGENMASS 1.047

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <asm-generic/fcntl.h>
# include "../libft/libft/libft.h"
# include "errors.h"

/*Map file analysis information and internal ds storage*/
typedef struct s_map
{
	int		max_x;
	int		max_y;
	int		chars_total;
	char	**map;
} t_map;

/*Player position expressed as a 2D vector*/
typedef struct s_pl_pos
{
	float	x;
	float	y;
	char direction;
	float player_angle;

}	t_pl_pos;

/*Rays, will need (screen width) number of those*/
typedef struct s_rays
{
	float	dir_x;
	float	dir_y;
	float	ray_angle;
}	t_rays;

/*Encapsulating other structs as abstractions / groups*/
typedef struct s_data
{
	t_map		*map;
	t_pl_pos	*pl_pos;
	t_rays		*rays;
}	t_data;

// map_parsing.c
int is_valid_map(t_data *data, char *map_filename);


#endif