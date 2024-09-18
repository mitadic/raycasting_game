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
	int		wall_w;
	int		wall_h;

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
			// printf("drawing pixel value: %lu for x: %d and for y: %d\n", *(uint32_t *)(img->data + increment), x, y);
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
    data->img_buff.img = mlx_xpm_file_to_image(data->mlx, "./textures/icon.xpm", &size_x, &size_y);
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

/*

PSEUDO

void	draw_a_column(t_data *data, int ray_idx, int texture_x_idx)
{
	int	texture;

	texture = determine_the_texture(data, ray_idx);
}

// While either x or y of the hitpoint are the same, increment wall_w
int	calculate_wall_w(t_data *data, int ray_idx)
{
	float	one_wall_hp_x;
	float	one_wall_hp_y;
	int		wall_w;

	wall_w = 0;
	one_wall_hp_x = data->rays[ray_idx].hp_x;
	one_wall_hp_y = data->rays[ray_idx].hp_y;
	while (data->rays[ray_idx + wall_w].hp_x == one_wall_hp_x || \
			data->rays[ray_idx + wall_w].hp_y == one_wall_hp_y)
		wall_w++;
	return (wall_w);
}

void	draw_a_wall(t_data *data, int *ray_idx)
{
	int wall_start;
	int	wall_w;
	int	wall_w_scale_factor;
	int	columns_to_repeat_count;

	wall_start = *ray_idx;
	wall_w = calculate_wall_w(data, *ray_idx); // count how many rays hit this one wall
	if (wall_w < TILE_SIZE)
	{
		wall_w_scale_factor = TILE_SIZE / (wall_w + 1); // let's assume w 3, so fct=16
		// that means we need pixels[16][y], [32][y], [48][y]
		while (*ray_idx < wall_start + wall_w)
		{
			draw_a_column(data, *ray_idx, ((*ray_idx - wall_start + 1) * wall_w_scale_factor))
			*ray_idx += 1;
		}
	}
	
	else if (wall_w >= TILE_SIZE)
	{
		wall_w_scale_factor = wall_w; // let's assume w 80, so fct = 80
		columns_to_repeat_count = wall_w_scale_factor - TILE_SIZE // 80 - 64 == 16
		// that means we repeat 16 columns. Where? At increments of TILE_SIZE/16==4
		// pixels[]
		while (*ray_no < wall_start + wall_w)
		{
			;
		}
	}
}


void	draw_columns
{
	int	i;

	i = 0;
	while (i < SCREEN_W)
		draw_a_wall(data, &i);
}

*/