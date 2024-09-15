#include "../../includes/cub3d.h"

void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x += cos(data->pl_pos.player_angle_degree) * MOV_SPEED;
	new_y = data->pl_pos.y += sin(data->pl_pos.player_angle_degree) * MOV_SPEED;
	data->pl_pos.x = new_x;
	data->pl_pos.y = new_y;
}

void	move_backward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x -= cos(data->pl_pos.player_angle_degree) * MOV_SPEED;
	new_y = data->pl_pos.y -= sin(data->pl_pos.player_angle_degree) * MOV_SPEED;
	data->pl_pos.x = new_x;
	data->pl_pos.y = new_y;
}

void	move_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
	new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
	data->pl_pos.x = new_x;
	data->pl_pos.y = new_y;
}

void	move_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
	new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
	data->pl_pos.x = new_x;
	data->pl_pos.y = new_y;
}

void	rotate_left(t_data *data)
{
	data->pl_pos.player_angle_radian -= ROT_SPEED;
    if (data->pl_pos.player_angle_radian < -M_PI) // If turned L beyond W (-180 deg)
        data->pl_pos.player_angle_radian += 2 * M_PI; // Switch to positive val
}

void	rotate_right(t_data *data)
{
	data->pl_pos.player_angle_radian += ROT_SPEED;
    if (data->pl_pos.player_angle_radian >= M_PI) // If turned R to W (beyond 179.999 deg)
        data->pl_pos.player_angle_radian -= 2 * M_PI; // Switch to negative val
}