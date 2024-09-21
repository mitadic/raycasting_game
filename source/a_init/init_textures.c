#include "../../includes/cub3d.h"

int	init_textures(t_data *data, char *map_filename)
{
	int	i;

	(void)map_filename;

	data->mlx = mlx_init();
	if (!data->mlx)
		error_and_bail(data, "mlx_init fail", KO);
	i = -1;
	while (++i < 4)
		data->txt[i].img = NULL;
	data->txt[0].img = mlx_xpm_file_to_image(data->mlx, "./textures/icon.xpm", &data->txt[0].size_x, &data->txt[0].size_y);
	data->txt[1].img = mlx_xpm_file_to_image(data->mlx, "./textures/test.xpm", &data->txt[1].size_x, &data->txt[1].size_y);
	data->txt[2].img = mlx_xpm_file_to_image(data->mlx, "./textures/cn3d.xpm", &data->txt[2].size_x, &data->txt[2].size_y);
	data->txt[3].img = mlx_xpm_file_to_image(data->mlx, "./textures/bmp_64x64.xpm", &data->txt[3].size_x, &data->txt[3].size_y);
	i = -1;
	while (++i < 4)
	{
		if (!data->txt[i].img)
			return (error(TEXTLOADFAIL, KO));
	}
	return (OK);
}