/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:21:25 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:18:23 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mlx || !data->win)
		return (1);
	if (keycode == KEY_ESC)
		bail(data, OK);
	else if (keycode == KEY_W)
		data->key_state.w = 1;
	else if (keycode == KEY_S)
		data->key_state.s = 1;
	else if (keycode == KEY_A)
		data->key_state.a = 1;
	else if (keycode == KEY_D)
		data->key_state.d = 1;
	else if (keycode == KEY_LEFT)
		data->key_state.left = 1;
	else if (keycode == KEY_RIGHT)
		data->key_state.right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mlx || !data->win)
		return (1);
	if (keycode == KEY_W)
		data->key_state.w = 0;
	else if (keycode == KEY_S)
		data->key_state.s = 0;
	else if (keycode == KEY_A)
		data->key_state.a = 0;
	else if (keycode == KEY_D)
		data->key_state.d = 0;
	else if (keycode == KEY_LEFT)
		data->key_state.left = 0;
	else if (keycode == KEY_RIGHT)
		data->key_state.right = 0;
	return (0);
}

int	close_x(t_data *data)
{
	bail(data, 0);
	return (0);
}
