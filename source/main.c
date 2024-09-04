#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data  data;

	if (argc != 2)
		return (error(PRINTUSAGE, 1));
	if (init(&data, argv[1]) != OK || validate_map(&data, argv[1]) != OK)
		bail(&data, 2);
	// int	y = -1;
	// int	x;
	// while (++y < data.map.max_y)
	// {
	// 	x = -1;
	// 	while (++x < data.map.max_x)
	// 		printf("%c", data.map.vals[y][x]);
	// 	printf("\n");
	// }
	purge(&data);
	return (OK);
}
