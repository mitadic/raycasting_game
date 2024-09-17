#include "textures.h"

//////////////////////////////////////////////////////////////////////
// FAKE

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

void	fst_mlx_pixel_put(t_data *data, int x, int y, uint32_t color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
		dst = data->img_buff.addr + (y * data->img_buff.line_length + x * \
				(data->img_buff.bits_per_pixel / 8));
		*(uint32_t *)dst = color;
	}
}

void	draw_single_column_px(t_data *data, int x, int y, uint32_t color)
{
	fst_mlx_pixel_put(data, x, y, color);
}

void	draw_columns_from_internal_ds(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < TILE_SIZE)
	{
		y = -1;
		while (++y < TILE_SIZE)
		{
			draw_single_column_px(data, x, y, data->texture[0].pixels[x][y]);
		}
	}
}

void	load_pxls_to_internal_ds(t_data *data, int size_x, int size_y)
{
	int		x;
	int		y;
	int		increment;
	t_img	*img;
	
	img = (t_img *)(data->img_buff.img);
	// printf("size_line is: %d\n", img->size_line);
	// printf("bpp is: %d\n", img->bpp);
	// printf("size_x is: %d\n", size_x);
	// printf("size_y is: %d\n", size_y);
	x = -1;
	while (++x < size_x)
	{
		y = -1;
		while (++y < size_y)
		{
			increment = (y * img->size_line) + (x * img->bpp / 8);
			data->texture[0].pixels[x][y] = *(uint32_t *)(img->data + increment);
		}
	}
}

void	draw_columns_pristinely(t_data *data, int size_x, int size_y)
{
	int		x;
	int		y;
	int		increment;
	t_img	*img;
	
	img = (t_img *)(data->img_buff.img);
	// printf("size_line is: %d\n", img->size_line);
	// printf("bpp is: %d\n", img->bpp);
	// printf("size_x is: %d\n", size_x);
	// printf("size_y is: %d\n", size_y);
	x = -1;
	while (++x < size_x)
	{
		y = -1;
		while (++y < size_y)
		{
			increment = (y * img->size_line) + (x * img->bpp / 8);
			draw_single_column_px(data, x, y, *(uint32_t *)(img->data + increment));
		}
	}
}

void	go_mlxing(t_data *data)
{
    data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "rendered");
	if (!data->win)
		exit(2);
    int size_x;
    int size_y;
    data->img_buff.img = mlx_xpm_file_to_image(data->mlx, "./textures/test.xpm", &size_x, &size_y);
	if (!data->img_buff.img)
        exit (3);
	// data->img_buff.img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->img_buff.addr = mlx_get_data_addr(data->img_buff.img, &data->img_buff.bits_per_pixel, \
		&data->img_buff.line_length, &data->img_buff.endian);
	printf("addr: %p, bpp: %d, line_length: %d, endian: %d\n", data->img_buff.addr, data->img_buff.bits_per_pixel, data->img_buff.line_length, data->img_buff.endian);

    // FAST PUT PIXELS TO IMG BUFFER HERE
    // draw_columns_pristinely(data, size_x, size_y);
	load_pxls_to_internal_ds(data, size_x, size_y);
	draw_columns_from_internal_ds(data);

    mlx_put_image_to_window(data->mlx, data->win, data->img_buff.img, 0, 0);
	mlx_do_sync(data->mlx);  // Forces synchronization of the MiniLibX display
    mlx_hook(data->win, 2, 1L << 0, close_esc, data);
	mlx_hook(data->win, 17, 1L << 3, close_x, (void *)data);
	mlx_loop(data->mlx);
}

//////////////////////////////////////////////////////////////////////
// REAL

// draw_single_column_px(data, x, y, data->texture[0].pixels[x][y]);

int main(void)
{
    t_data  data;

    go_mlxing(&data);
}