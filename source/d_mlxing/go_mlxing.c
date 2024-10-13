/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_mlxing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:57:33 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:16:46 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	handle_movement(t_data *data)
{
	if (data->key_state.w)
		move_forward(data);
	if (data->key_state.s)
		move_backward(data);
	if (data->key_state.a)
		move_left(data);
	if (data->key_state.d)
		move_right(data);
	if (data->key_state.left)
		rotate_left(data);
	if (data->key_state.right)
		rotate_right(data);
}

// the core repeat logic of prg runtime, called forth by mlx_loop_hook() 
/*draws main game to the image buffer, puts main game image buffer to 
window first and finally puts minimap on top of it*/
int	continuous_rendering(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!is_time_to_render(data))
		return (0);
	handle_movement(data);
	math(data);
	draw_columns(data);
	if (BONUS_ENABLED)
	{
		initialize_minimap(data);
		draw_minimap_on_image(data, &data->minimap); 
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_buff.img, 0, 0);
	if (BONUS_ENABLED)
		mlx_put_image_to_window(data->mlx, data->win,
			data->minimap.img, 10, 10);
	return (0);
}

// mlx_init happens earlier, because needed to load the textures
/*mlx_loop_hook registers the continuous rendering loop*/
/*mlx_loop starts the MLX event loop*/
void	go_mlxing(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (!data->win)
		error_and_bail(data, "mlx_new_window fail", KO);
	data->img_buff.img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->img_buff.addr = mlx_get_data_addr(data->img_buff.img,
			&data->img_buff.bits_per_pixel,
			&data->img_buff.line_length, &data->img_buff.endian);
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win, 17, 1L << 3, close_x, (void *)data);
	if (BONUS_ENABLED)
	{
		mlx_hook(data->win, 4, 1L << 2, handle_mouse_scroll_up, data);
		mlx_hook(data->win, 5, 1L << 3, handle_mouse_scroll_down, data);
	}
	mlx_loop_hook(data->mlx, continuous_rendering, data);
	mlx_loop(data->mlx);
}
