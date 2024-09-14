#include "../../includes/cub3d.h"

int	close_esc(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->mlx && data->win)
	{
		if (keycode == 0xff1b)
		{
			mlx_destroy_window(data->mlx, data->win);
			exit(0);
		}
	}
	return (0);
}

int	close_x(t_data *data)
{
	(void)data;
	exit(0);
}

/*
1	data->img_buff.addr	- address of the very first pixel
2	y * data->img_buff.line_length - pixel row count
3	x * data->img_buff.bits_per_pixel / 8 - pixel column count
Result: add them all up, you access a pixels's memory address by using x and y
*/
void	fst_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
		dst = data->img_buff.addr + (y * data->img_buff.line_length + x * \
				(data->img_buff.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_columns(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
		{
			;
		}
	}
}

void	go_mlxing(t_data *data)
{
    data->mlx = mlx_init();
	if (!data->mlx)
		error_and_bail(data, "mlx_init fail", KO);
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (!data->win)
		error_and_bail(data, "mlx_new_window fail", KO);
	data->img_buff.img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->img_buff.addr = mlx_get_data_addr(data->img_buff.img, &data->img_buff.bits_per_pixel, \
		&data->img_buff.line_length, &data->img_buff.endian);
    // FAST PUT PIXELS TO IMG BUFFER HERE
	math(data);
	draw_columns(data);
    // OBSOLETE from fdf for reference:
        // points_2d(vars);
        // edges(vars, img);
	mlx_put_image_to_window(data->mlx, data->win, data->img_buff.img, 0, 0);
	mlx_hook(data->win, 2, 1L << 0, close_esc, (void *)data);
	mlx_hook(data->win, 17, 1L << 3, close_x, (void *)data);
	mlx_loop(data->mlx);
}