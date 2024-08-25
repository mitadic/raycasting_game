#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft/libft.h"
# include "errors.h"

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
}	t_pl_pos;

typedef struct s_data
{
	t_map		*map;
	t_pl_pos	*pl_pos;
}	t_data;

// map_parsing.c
int	is_valid_map(char *map_filename)

#endif