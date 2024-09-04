#include "../includes/cub3d.h"

void	free_map_copy(char **map_copy, int rows_allocated)
{
	int	y;

	if (!map_copy)
		return ;
	y = -1;
	while (++y < rows_allocated)
		free(map_copy[y]);
	free(map_copy);
}

static int	malloc_for_map_copy(t_data *data, char ***map_copy, int y)
{
	*map_copy = malloc(sizeof(char *) * data->map.max_y);
	if (!*map_copy)
		return (error(MALLOCFAIL, KO));
	while (++y < data->map.max_y)
	{
		(*map_copy)[y] = malloc(sizeof(char) * data->map.max_x);
		if (!(*map_copy)[y])
		{
			free_map_copy(*map_copy, y);
			return (error(MALLOCFAIL, KO));
		}
	}
	return (OK);
}

/* Copy entire map, replace the pl_pos with '0' for flood_simulation */
static int	copy_map(t_data *data, char ***map_copy)
{
	int	y;
	int	x;

	y = -1;
	if (malloc_for_map_copy(data, map_copy, y) != OK)
		return (KO);
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			(*map_copy)[y][x] = data->map.vals[y][x];
			if (ft_strchr(PLAYER_DIR, data->map.vals[y][x]))
				(*map_copy)[y][x] = '0';
		}
	}
	return (OK);
}

/* Time and again I'm astonished by pointers.
We delegate malloc'ing to a function using &map_copy
But we can access the allocated memory space equally well and store and
manipulate data, for the purposes of flood_sim(), using <map_copy> as a copy.
- copy_map(&map_copy)
- flood_simulation(map_copy)
*/
int	flood_fill(t_data *data)
{
	char    **map_copy;

	if (copy_map(data, &map_copy) != OK)
		return (KO);
	if (flood_simulation(data, map_copy) != OK)
	{
		free_map_copy(map_copy, data->map.max_y);
		return (KO);
	}
	free_map_copy(map_copy, data->map.max_y);
	return (OK);
}