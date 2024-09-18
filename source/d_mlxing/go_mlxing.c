#include "../../includes/cub3d.h"

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

void	draw_single_column(t_data *data, int x, int y)
{
	int		wall_start;
	int		wall_end;
	float	wall_h;
	int		color;

	wall_h = data->rays[x].wall_height;
	wall_start = (SCREEN_H - wall_h) / 2;
	wall_end = wall_start + wall_h - 1;
	if (y < wall_start)
		fst_mlx_pixel_put(data, x, y, WHITE);
	else if (y > wall_end)
		fst_mlx_pixel_put(data, x, y, BLACK);
	else
	{
		 if (data->rays[x].wall_to_the == 'N')
			color = BLUE;
		else if (data->rays[x].wall_to_the == 'E')
			color = YELLOW;
		else if (data->rays[x].wall_to_the == 'S')
			color = RED;
		else if (data->rays[x].wall_to_the == 'W')
			color = ORANGE;
		else // corners
			color = WHITE; 
		fst_mlx_pixel_put(data, x, y, color);
	}
}

void	draw_columns(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
			draw_single_column(data, x, y);
	}
}

int	handle_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mlx || !data->win)
		return(1);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		bail(data, 0);
	}
	else if (keycode == KEY_W) data->key_state.w = 1;
	else if (keycode == KEY_S) data->key_state.s = 1;
	else if (keycode == KEY_A) data->key_state.a = 1;
	else if (keycode == KEY_D) data->key_state.d = 1;
	else if (keycode == KEY_LEFT) data->key_state.left = 1;
	else if (keycode == KEY_RIGHT) data->key_state.right = 1;
	printf("key pressed is %i\n", keycode);
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mlx || !data->win)
		return(1);
	if (keycode == KEY_W) data->key_state.w = 0;
	else if (keycode == KEY_S) data->key_state.s = 0;
	else if (keycode == KEY_A) data->key_state.a = 0;
	else if (keycode == KEY_D) data->key_state.d = 0;
	else if (keycode == KEY_LEFT) data->key_state.left = 0;
	else if (keycode == KEY_RIGHT) data->key_state.right = 0;
	return (0);
}

int	close_x(t_data *data)
{
	bail(data, 0);
	return(0);
	
}



int	is_time_to_render(t_data *data)
{
	struct timeval	diff;
	struct timeval	current;
	struct timeval	last_render;

	last_render = data->time.last_render;
	if (last_render.tv_sec == 0)
	{
		gettimeofday(&data->time.last_render, NULL);
		return (BOOL_YES);
	}
	gettimeofday(&current, NULL);
	diff.tv_sec = current.tv_sec - last_render.tv_sec;
	diff.tv_usec = current.tv_usec - last_render.tv_usec;
	if (current.tv_usec < last_render.tv_usec)
		diff.tv_usec = current.tv_usec + MICROSEC_PER_S - last_render.tv_usec;
	if (diff.tv_usec >= MICROSEC_PER_S / PLAY_FPS)
	{
		gettimeofday(&data->time.last_render, NULL);
		return (BOOL_YES);
	}
	return (BOOL_NO);
}


int	continuous_rendering(void *param)
{

	
	t_data *data = (t_data *)param;

	if(!is_time_to_render(data))
		return (0);
	if (data->key_state.w) move_forward(data);
	if (data->key_state.s) move_backward(data);
	if (data->key_state.a) move_left(data);
	if (data->key_state.d) move_right(data);
	if (data->key_state.left) rotate_left(data);
	if (data->key_state.right) rotate_right(data);

	// Clear the image buffer? Seems to be acting glitchy
	// mlx_clear_window(data->mlx, data->win);

	// Do raycasting anew
	math(data);
	draw_columns(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_buff.img, 0, 0);
	return (0);
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
    mlx_hook(data->win, 2, 1L << 0, handle_keypress, data); // Key press (mov, Esc...)
	mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);  // Key release event
	mlx_hook(data->win, 17, 1L << 3, close_x, (void *)data);
	// Register the continuous rendering loop
    mlx_loop_hook(data->mlx, continuous_rendering, data);
	// Start the MLX event loop
	mlx_loop(data->mlx);
}