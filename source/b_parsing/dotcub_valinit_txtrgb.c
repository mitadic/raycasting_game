#include "../../includes/cub3d.h"

static int	pack_rgb(int red, int green, int blue)
{
    return ((red << 16) | (green << 8) | blue) & 0xFFFFFF;
}

/* TODO */
int val_init_rgbs(t_data *data)
{
    int	i;

	if (!is_textures_and_rgbs_complete(data))
		return (KO);
	i = -1;
	while (++i < 3)
	{
		if (data->map.ceiling[i] < 0 || data->map.floor[i] < 0 || \
			data->map.ceiling[i] > 255 || data->map.floor[i] > 255)
			return (error("bad RGB values", KO));
	}
	data->map.rgb_c = pack_rgb(data->map.ceiling[0], data->map.ceiling[1], \
								data->map.ceiling[2]);
	data->map.rgb_f = pack_rgb(data->map.floor[0], data->map.floor[1], \
								data->map.floor[2]);
	return (OK);
}

int	val_init_textures(t_data *data)
{
	int		i;
	t_img	*tx_img;

	data->mlx = mlx_init();
	if (!data->mlx)
		error_and_bail(data, "mlx_init fail", KO);
	i = -1;
	while (++i < 4)
		data->txt[i].img = NULL;
	printf("map.no: %s\n", data->map.no);
	printf("map.ea: %s\n", data->map.ea);
	printf("map.so: %s\n", data->map.so);
	printf("map.we: %s\n", data->map.we);
	if (access(data->map.no, R_OK) == 0)
		printf("access to map.no: AYE\n");
	data->txt[0].img = mlx_xpm_file_to_image(data->mlx, data->map.no, &data->txt[0].size_x, &data->txt[0].size_y);
	data->txt[1].img = mlx_xpm_file_to_image(data->mlx, data->map.ea, &data->txt[1].size_x, &data->txt[1].size_y);
	data->txt[2].img = mlx_xpm_file_to_image(data->mlx, data->map.so, &data->txt[2].size_x, &data->txt[2].size_y);
	data->txt[3].img = mlx_xpm_file_to_image(data->mlx, data->map.we, &data->txt[3].size_x, &data->txt[3].size_y);
	printf("%p\n", data->txt[0].img);
	printf("%p\n", data->txt[1].img);
	printf("%p\n", data->txt[2].img);
	printf("%p\n", data->txt[3].img);
	i = -1;
	while (++i < 4)
	{
		tx_img = data->txt[i].img;
		if (!tx_img || !tx_img->data)
			return (error(TEXTLOADFAIL, KO));
		if (tx_img->height != tx_img->width)
			return (error(NOTSQUARE, KO));
	}
	return (OK);
}

int	val_init_txtrgb(t_data *data)
{
	if (val_init_rgbs(data) != OK)
		return (KO);
	if (val_init_textures(data) != OK)
		return (KO);
	return (OK);
}
