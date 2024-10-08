#include "../../includes/cub3d.h"

/*
1	data->img_buff.addr	- address of the very first pixel
2	y * data->img_buff.line_length - pixel row count
3	x * data->img_buff.bits_per_pixel / 8 - pixel column count
Result: add them all up, you access a pixels's memory address by using x and y
*/
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

// determines the float to use to scale & determine the x idx of texture
float	get_the_float_component_of_hitp(t_data *data, int x)
{
	double	hp_float_x;
	double	hp_float_y;
	double	throwaway_int_x;
	double	throwaway_int_y;

	hp_float_x = modf(data->rays[x].hit_x, &throwaway_int_x);
	hp_float_y = modf(data->rays[x].hit_y, &throwaway_int_y);
	if (data->rays[x].side == VERTICAL)
		return (hp_float_x);
	return (hp_float_y);
}

/*
tx_x: scaled hitpoint value vs. texture image width to determine the tx px row
tx_y: scaled current image row px vs. tx_img->height to find tx_px[tx_x][tx_y]
*/
int		determine_wrp_texture_pixel(t_data *data, int x, int y, t_img *tx_img)
{
	int		tx_x;
	int		tx_y;
	int		increment;
	int		wall_start;

	wall_start = (SCREEN_H - data->rays[x].wall_height) / 2;
	if (!tx_img)
		return (WHITE);
	tx_x = (int)(get_the_float_component_of_hitp(data, x) * tx_img->width);
	tx_y = (int)((y - wall_start) / data->rays[x].wall_height * tx_img->height);
	if (tx_y == tx_img->height)
		tx_y -= 1;
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

/* Draw ceiling pixels, then texture pixels, then floor pixels */
void	draw_a_column(t_data *data, int x, int wall_h)
{
	int		wall_start;
	int		wall_end;
	int		y;

	wall_start = (SCREEN_H - wall_h) / 2;
	wall_end = wall_start + wall_h - 1;
	y = 0;
	while (y < wall_start) // ceiling
	{
		fst_mlx_pixel_put(data, x, y, data->map.rgb_c);
		y++;
	}
	draw_wall_texture_pxs(data, x, &y); // texture
	while (y > wall_end && y < SCREEN_H)
	{
		fst_mlx_pixel_put(data, x, y, data->map.rgb_f); // floor
		y++;
	}
}

void	draw_columns(t_data *data)
{
	int	ray_idx;

	ray_idx = -1;
	while (++ray_idx < SCREEN_W)
		draw_a_column(data, ray_idx, data->rays[ray_idx].wall_height);
}
