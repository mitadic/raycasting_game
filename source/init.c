#include "../includes/cub3d.h"

/* malloc for char **map using max_vector_values */
static int	malloc_for_map_vals(t_data *data)
{
	int	y;

	data->map.vals = malloc(sizeof(char *) * data->map.max_y);
	if (!data->map.vals)
		return (error(MALLOCFAIL, KO));
	y = -1;
	while (++y < data->map.max_y)
	{
		data->map.vals[y] = malloc(sizeof(char) * data->map.max_x);
		if (!data->map.vals[y])
			return (error(MALLOCFAIL, KO));
	}
	return (OK);
}

/* open the map file for the sole purpose of finding max x and y values */
static int	set_max_vector_values(t_data *data, char *map_filename)
{
	int	fd;
	char *line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	line = get_next_line(fd);
	data->map.max_x = ft_strlen(line) - ENDLINE;
	while (line)
	{
		data->map.max_y += 1;
		if ((int)(ft_strlen(line) - ENDLINE) > data->map.max_x)
			data->map.max_x = ft_strlen(line) - ENDLINE;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		return (error(CANTCLOSE, KO));
	if (data->map.max_x < 3 || data->map.max_y < 3)
		return (error(MAPTOOTINY, KO));
	return (OK);
}

int	init(t_data *data, char *map_filename)
{
	data->map.max_x = 0;
	data->map.max_y = 0;
	data->map.vals = NULL;
	data->rays = malloc(sizeof(t_rays) * SCREEN_W);
	if (!data->rays)
		return (error(MALLOCFAIL, KO));
	if (set_max_vector_values(data, map_filename) != OK || \
			malloc_for_map_vals(data) != OK)
		return (KO);
	return (OK);
}
