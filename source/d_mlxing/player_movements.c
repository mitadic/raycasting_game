/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:00:44 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:16:32 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define PLAYER_RADIUS 0.1
#define COLLISION_BUFFER 0.2 //can be modified

/* Convert player's position to map coordinates */
/* Calculate buffered positions */
/* Convert buffered positions to map coordinates */
/* Check if any of these positions hit a wall */
int	is_wall(float new_x_pos, float new_y_pos, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x_pos;
	map_y = (int)new_y_pos;
	data->pl_pos.buffered_x_left = new_x_pos - COLLISION_BUFFER;
	data->pl_pos.buffered_x_right = new_x_pos + COLLISION_BUFFER;
	data->pl_pos.buffered_y_up = new_y_pos - COLLISION_BUFFER;
	data->pl_pos.buffered_y_down = new_y_pos + COLLISION_BUFFER;
	data->pl_pos.map_x_left = (int)data->pl_pos.buffered_x_left;
	data->pl_pos.map_x_right = (int)data->pl_pos.buffered_x_right;
	data->pl_pos.map_y_up = (int)data->pl_pos.buffered_y_down;
	data->pl_pos.map_y_down = (int)data->pl_pos.buffered_y_down;
	if (data->map.vals[map_x][map_y] == '1' ||
		data->map.vals[data->pl_pos.map_x_left][map_y] == '1' || 
		data->map.vals[data->pl_pos.map_x_right][map_y] == '1' ||
		data->map.vals[map_x][data->pl_pos.map_y_up] == '1' ||
		data->map.vals[map_x][data->pl_pos.map_y_down] == '1')
	{
		return (1);
	}
	return (0);
}

void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_radian) * MOV_SPEED;
	new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_radian) * MOV_SPEED;
	if (!is_wall(new_x, data->pl_pos.y, data))
		data->pl_pos.x = new_x;
	if (!is_wall(data->pl_pos.x, new_y, data))
		data->pl_pos.y = new_y;
}

void	move_backward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_radian) * MOV_SPEED;
	new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_radian) * MOV_SPEED;
	if (!is_wall(new_x, data->pl_pos.y, data))
		data->pl_pos.x = new_x;
	if (!is_wall(data->pl_pos.x, new_y, data))
		data->pl_pos.y = new_y;
}

void	move_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_radian + M_PI / 2)
		* MOV_SPEED;
	new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_radian + M_PI / 2)
		* MOV_SPEED;
	if (!is_wall(new_x, data->pl_pos.y, data))
		data->pl_pos.x = new_x;
	if (!is_wall(data->pl_pos.x, new_y, data))
		data->pl_pos.y = new_y;
}

void	move_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_radian + M_PI / 2)
		* MOV_SPEED;
	new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_radian + M_PI / 2)
		* MOV_SPEED;
	if (!is_wall(new_x, data->pl_pos.y, data))
		data->pl_pos.x = new_x;
	if (!is_wall(data->pl_pos.x, new_y, data))
		data->pl_pos.y = new_y;
}
