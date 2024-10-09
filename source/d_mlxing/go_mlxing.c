#include "../../includes/cub3d.h"

int	handle_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mlx || !data->win)
		return(1);
	if (keycode == KEY_ESC)
		bail(data, OK);
	else if (keycode == KEY_W) data->key_state.w = 1;
	else if (keycode == KEY_S) data->key_state.s = 1;
	else if (keycode == KEY_A) data->key_state.a = 1;
	else if (keycode == KEY_D) data->key_state.d = 1;
	else if (keycode == KEY_LEFT) data->key_state.left = 1;
	else if (keycode == KEY_RIGHT) data->key_state.right = 1;
	// printf("key pressed is %i\n", keycode);
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

// use gettimeofday() to store the time of last_render and limit the FPS
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
void clear_image_buffer(t_img_buff *buffer, t_data *data) 
{
	int i = 0;
    // assuming minimap is initialized correctly
    if (buffer == NULL) return; // pprevent null dereference


(void)data;
    int total_pixels = buffer->width * buffer->height;
    unsigned int *data_ptr = (unsigned int *)buffer;

    while (i < total_pixels) 
    {
        data_ptr[i] = 0xFFFFFF; // Clear to white or any color you want for empty space
		i++;
    }
	
}

// the core repeat logic of prg runtime, called forth by mlx_loop_hook() 
int continuous_rendering(void *param)
{
    t_data *data = (t_data *)param;

    if (!is_time_to_render(data))
        return (0);
    if (data->key_state.w) move_forward(data);
    if (data->key_state.s) move_backward(data);
    if (data->key_state.a) move_left(data);
    if (data->key_state.d) move_right(data);
    if (data->key_state.left) rotate_left(data);
    if (data->key_state.right) rotate_right(data);

    // clear  image buffer
    //clear_image_buffer(&data->img_buff, data);

    math(data);
    // draw  main game to the image buffer
    draw_columns(data);
    // If BONUS is enabled, draw the minimap
    if (BONUS)
    {
        initialize_minimap(data);
        draw_minimap_on_image(data, &data->minimap); 
    }
    // put main game image buffer to window first
    mlx_put_image_to_window(data->mlx, data->win, data->img_buff.img, 0, 0);

    // put minimap on top of it
    if (BONUS)
    {
        mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 10, 10); // display minimap at (10,10)
    }

    return (0);
}

// mlx_init happens earlier, because needed to load the textures
void	go_mlxing(t_data *data)
{
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