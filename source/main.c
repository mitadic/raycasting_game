#include "../includes/cub3d.h"

static int	print_usage(int exit_status)
{
	printf("Error\n");
	printf("Usage: ./cub3d some_cub3d_compliant_map.cub\n");
	return (exit_status);
}

static int	set_max_vector_values(t_data *data, char *map_filename)
{
	int	fd;
	char *line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	line = getnextline(fd);
	data->map.max_x = ft_strlen(line);
	while (line)
	{
		data->map.max_y += 1;
		if (ft_strlen(line) > data->map.max_x)
			data->map.max_x = ft_strlen(line);
		free(line);
		line = getnextline(fd);
	}
	close(fd);
	return (OK);
}

static int	init_values(t_data *data, char *map_filename)
{
	data->pl_pos = malloc(sizeof(t_pl_pos));
	data->map = malloc(sizeof(t_map));
	if (!data->pl_pos || !data->map)
	{
		printf("malloc fail\n");
		return (purge(data, KO));
	}
	data->pl_pos.x = 0;
	data->pl_pos.y = 0;
	data->map.max_x = 0;
	data->map.max_y = 0;
	data->map.chars_total = 0;
	if (set_max_vector_values(data, map_filename) != OK)
		return (purge(data, KO));
	// now malloc for char **map using max_vector_values
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data  data;

	if (argc != 2)
		return (print_usage(1));
	if (init_values(&data, argv[1]) != OK)
		return (1);
	if (!is_valid_map(&data, argv[1]))
		return (2);
}
