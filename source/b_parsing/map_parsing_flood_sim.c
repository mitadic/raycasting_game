#include "../../includes/cub3d.h"

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
			if (map[x][y] == '0')
				return (error(AIRPOCKETS, KO));
			if ((y == 0 || y == data->map.max_y - 1 || \
					x== 0 || x == data->map.max_x - 1) && \
					map[x][y] == 'W')
				return (error(LEAKYMAP, KO));
		}
	}
	return (OK);
}

/* recursive Paint fill tool, NESW */
static void	flood_fields(t_data *data, char **map, int x, int y)
{
	if (map[x][y] == '0')
		map[x][y] = 'W';
	if (y > 0 && map[x][y - 1] == '0')
		flood_fields(data, map, x, y - 1);
	if (x < data->map.max_x - 1 && map[x + 1][y] == '0')
		flood_fields(data, map, x + 1, y);
	if (y < data->map.max_y - 1 && map[x][y + 1] == '0')
		flood_fields(data, map, x, y + 1);
	if (x > 0 && map[x - 1][y] == '0')
		flood_fields(data, map, x - 1, y);
}

/* Locate first available '0' to start the flood at.
At this point, we know that at the very least the player field exist,
which at this stage has been replaced with a '0' so we will find sth. */
static void	get_start_coords(t_data *data, char **map_copy, int (*coords)[2])
{
	int y;
	int x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (map_copy[x][y] == '0')
			{
				(*coords)[0] = x;
				(*coords)[1] = y;
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