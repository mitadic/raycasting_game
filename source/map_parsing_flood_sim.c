#include "../includes/cub3d.h"

static int	scan_for_dry_fields(t_data *data, char **map)
{
	int y;
	int x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (map[y][x] == '0')
				return (error(AIRPOCKETS, KO));
			if ((y == data->map.max_y - 1 || x == data->map.max_x) && \
					map[y][x] == 'W')
				return (error(LEAKYMAP, KO));
		}
	}
	return (OK);
}

/* recursive Paint fill tool, NESW */
static void	flood_fields(t_data *data, char **map, int y, int x)
{
	if (map[y][x] == '0')
		map[y][x] = 'W';
	if (y > 0 && map[y - 1][x] == '0')
		flood_fields(data, map, y - 1, x);
	if (x < data->map.max_x - 1 && map[y][x + 1] == '0')
		flood_fields(data, map, y, x + 1);
	if (y < data->map.max_y - 1 && map[y + 1][x] == '0')
		flood_fields(data, map, y + 1, x);
	if (x > 0 && map[y][x - 1] == '0')
		flood_fields(data, map, y, x - 1);
}

/* Locate first available '0' to start the flood at.
At this point, we know that at the very least the player field exist,
which at this stage has been replaced with a '0' so we will find sth. */
static void	get_start_coords(t_data *data, char **map_copy, int **coords)
{
	int y;
	int x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (data->map.vals[y][x] == '0')
			{
				(*coords)[0] = y;
				(*coords)[1] = x;
				return ;
			}
		}
	}
}

/* get_start_coords and flood_fields guarranteed to be yielding. Go. */
int	flood_simulation(t_data *data, char **map_copy)
{
	int start_coords[2];

	get_start_coords(data, map_copy, &start_coords);
	flood_fields(data, map_copy, start_coords[0], start_coords[1]);
	if (scan_for_dry_fields(data, map_copy) != OK)
		return (KO);
	return (OK);
}