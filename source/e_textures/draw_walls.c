#include "../../includes/cub3d.h"

void	fst_mlx_pixel_put(t_data *data, int x, int y, uint32_t color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
		dst = data->img_buff.addr + (y * data->img_buff.line_length + x * \
				(data->img_buff.bits_per_pixel / 8));
		*(uint32_t *)dst = color;
		// printf("color is: %d\n", color);
	}
}

// determines the float to use to scale & determine the x idx of texture
float	get_the_float_component_of_hitp(t_data *data, int x)
{
	double	hp_float_x;
	double	hp_float_y;
	double	throwaway_int_x;
	double	throwaway_int_y;

	hp_float_x = modf(data->rays[x].hit_x, &throwaway_int_x);
	hp_float_y = modf(data->rays[x].hit_y, &throwaway_int_y);
	if (hp_float_x > hp_float_y)
		return (hp_float_x);
	return (hp_float_y);
}

int		determine_wrp_texture_pixel(t_data *data, int x, int y, t_img *tx_img)
{
	int		tx_x;
	int		tx_y;
	int		increment;
	int		wall_start;

	wall_start = (SCREEN_H - data->rays[x].wall_height) / 2;
	if (!tx_img)
		return (WHITE);
	tx_x = (int)round(get_the_float_component_of_hitp(data, x) / (1.0 / tx_img->width));
	// tx_y = (int)round(tx_img->height / data->rays[x].wall_height) * ((y - wall_start + 1) % (int)(data->rays[x].wall_height));
	tx_y = (int)((y - wall_start) / (float)data->rays[x].wall_height * tx_img->height);
	increment = (tx_y * tx_img->size_line) + (tx_x * tx_img->bpp / 8);
	return (*(uint32_t *)(tx_img->data + increment));
}

void	draw_wall_texture_pxs(t_data *data, int x, int *y)
{
	t_img	*tx_img;
	int		i;
	int		color;

	tx_img = NULL;
	if (data->rays[x].wall_to_the == 'N')
		tx_img = (t_img *)(data->txt[WALL_N].img);
	else if (data->rays[x].wall_to_the == 'E')
		tx_img = (t_img *)(data->txt[WALL_E].img);
	else if (data->rays[x].wall_to_the == 'S')
		tx_img = (t_img *)(data->txt[WALL_S].img);
	else if (data->rays[x].wall_to_the == 'W')
		tx_img = (t_img *)(data->txt[WALL_W].img);
	i = -1;
	while (++i < data->rays[x].wall_height)
	{
		color = determine_wrp_texture_pixel(data, x, *y, tx_img);
		fst_mlx_pixel_put(data, x, *y, color);
		*y += 1;
	}
}

void	draw_column_pxs(t_data *data, int x, int *y, int wall_h)
{
	int		wall_start;
	int		wall_end;

	wall_start = (SCREEN_H - wall_h) / 2;
	wall_end = wall_start + wall_h - 1;
	if (*y < wall_start)
	{
		fst_mlx_pixel_put(data, x, *y, WHITE);
		*y += 1;
	}
	else if (*y > wall_end)
	{
		fst_mlx_pixel_put(data, x, *y, BLACK);
		*y += 1;
	}
	else
		draw_wall_texture_pxs(data, x, y);
}

void	draw_a_column(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < SCREEN_H)
		draw_column_pxs(data, x, &y, data->rays[x].wall_height);
}

// While either x or y of the hitpoint are the same, increment wall_w
int	calculate_wall_w(t_data *data, int ray_idx)
{
	float	one_wall_hp_x;
	float	one_wall_hp_y;
	int		wall_w;

	wall_w = 0;
	one_wall_hp_x = data->rays[ray_idx].hit_x;
	one_wall_hp_y = data->rays[ray_idx].hit_y;
	while (data->rays[ray_idx + wall_w].hit_x == one_wall_hp_x || \
			data->rays[ray_idx + wall_w].hit_y == one_wall_hp_y)
		wall_w++;
	return (wall_w);
}

void	draw_a_wall(t_data *data, int *ray_idx)
{
	int wall_start;
	int	wall_w;

	wall_start = *ray_idx;
	wall_w = calculate_wall_w(data, *ray_idx); // count how many rays hit this one wall
	while (*ray_idx < wall_start + wall_w)
	{
		draw_a_column(data, *ray_idx);
		*ray_idx += 1;
	}
}


void	draw_walls(t_data *data)
{
	int	ray_idx;

	ray_idx = 0;
	while (ray_idx < SCREEN_W)
		draw_a_wall(data, &ray_idx);
}


/*
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
*/