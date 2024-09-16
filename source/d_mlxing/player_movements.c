#include "../../includes/cub3d.h"
#define WALL '1'
#define PLAYER_RADIUS 0.1 // Small radius for the player to avoid "corner sticking"

// Function to check if a position is a wall
int is_wall(float x, float y, t_data *data)
{
    int mapX = (int)x;
    int mapY = (int)y;
    return (data->map.vals[mapX][mapY] == WALL); // Note: map indexing might be map[mapX][mapY] depending on your map storage
}
// void	move_forward(t_data *data)
// {
// 	float	new_x;
// 	float	new_y;

// 	new_x = data->pl_pos.x += cos(data->pl_pos.player_angle_degree) * MOV_SPEED;
// 	new_y = data->pl_pos.y += sin(data->pl_pos.player_angle_degree) * MOV_SPEED;
	
// 	    if (!is_wall(new_x, data->pl_pos.y, data))
//         data->pl_pos.x = new_x;
//     if (!is_wall(data->pl_pos.x, new_y, data))
//         data->pl_pos.y = new_y;
// }

// 	// data->pl_pos.x = new_x;
// 	// data->pl_pos.y = new_y;


// void	move_backward(t_data *data)
// {
// 	float	new_x;
// 	float	new_y;

// 	new_x = data->pl_pos.x -= cos(data->pl_pos.player_angle_degree) * MOV_SPEED;
// 	new_y = data->pl_pos.y -= sin(data->pl_pos.player_angle_degree) * MOV_SPEED;

// 	    if (!is_wall(new_x, data->pl_pos.y, data))
//         data->pl_pos.x = new_x;
//     if (!is_wall(data->pl_pos.x, new_y, data))
//         data->pl_pos.y = new_y;
// }
// 	// data->pl_pos.x = new_x;
// 	// data->pl_pos.y = new_y;
 

// void	move_left(t_data *data)
// {
// 	float	new_x;
// 	float	new_y;

// 	new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
// 	new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
	
//     if (!is_wall(new_x, data->pl_pos.y, data))
//         data->pl_pos.x = new_x;
//     if (!is_wall(data->pl_pos.x, new_y, data))
//         data->pl_pos.y = new_y;
// }
// 	// data->pl_pos.x = new_x;
// 	// data->pl_pos.y = new_y;


// void	move_right(t_data *data)
// {
// 	float	new_x;
// 	float	new_y;

// 	new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
// 	new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_degree + M_PI / 2) * MOV_SPEED;
// 	    if (!is_wall(new_x, data->pl_pos.y, data))
//         data->pl_pos.x = new_x;
//     if (!is_wall(data->pl_pos.x, new_y, data))
//         data->pl_pos.y = new_y;
// }

// 	// data->pl_pos.x = new_x;
// 	// data->pl_pos.y = new_y;


void	rotate_left(t_data *data)
{
	data->pl_pos.player_angle_degree -= ROT_SPEED * 50;
    if (data->pl_pos.player_angle_degree < -180) // If turned L beyond W (-180 deg)
        data->pl_pos.player_angle_degree += 360; // Switch to positive val
}

void	rotate_right(t_data *data)
{
	data->pl_pos.player_angle_degree += ROT_SPEED * 50;
    if (data->pl_pos.player_angle_degree >= 180) // If turned R to W (beyond 179.999 deg)
        data->pl_pos.player_angle_degree -= 360; // Switch to negative val
}
 
////////////////////////////////////////////////////


void move_forward(t_data *data)
{
    float new_x;
    float new_y;


    new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_radian) * MOV_SPEED;
    new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_radian) * MOV_SPEED;


    if (!is_wall(new_x, data->pl_pos.y, data))
        data->pl_pos.x = new_x;
    if (!is_wall(data->pl_pos.x, new_y, data))
        data->pl_pos.y = new_y;
}

void move_backward(t_data *data)
{
    float new_x;
    float new_y;


    new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_radian) * MOV_SPEED;
    new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_radian) * MOV_SPEED;


    if (!is_wall(new_x, data->pl_pos.y, data))
        data->pl_pos.x = new_x;
    if (!is_wall(data->pl_pos.x, new_y, data))
        data->pl_pos.y = new_y;
}

void move_left(t_data *data)
{
    float new_x;
    float new_y;


    new_x = data->pl_pos.x - cos(data->pl_pos.player_angle_radian + M_PI / 2) * MOV_SPEED;
    new_y = data->pl_pos.y - sin(data->pl_pos.player_angle_radian + M_PI / 2) * MOV_SPEED;

    if (!is_wall(new_x, data->pl_pos.y, data))
        data->pl_pos.x = new_x;
    if (!is_wall(data->pl_pos.x, new_y, data))
        data->pl_pos.y = new_y;
}

void move_right(t_data *data)
{
    float new_x;
    float new_y;


    new_x = data->pl_pos.x + cos(data->pl_pos.player_angle_radian + M_PI / 2) * MOV_SPEED;
    new_y = data->pl_pos.y + sin(data->pl_pos.player_angle_radian + M_PI / 2) * MOV_SPEED;

 
    if (!is_wall(new_x, data->pl_pos.y, data))
        data->pl_pos.x = new_x;
    if (!is_wall(data->pl_pos.x, new_y, data))
        data->pl_pos.y = new_y;
}

// void rotate_left(t_data *data)
// {

//     data->pl_pos.player_angle_radian -= ROT_SPEED;


//     if (data->pl_pos.player_angle_radian < -M_PI)
//         data->pl_pos.player_angle_radian += 2 * M_PI;
// }

// void rotate_right(t_data *data)
// {

//     data->pl_pos.player_angle_radian += ROT_SPEED;


//     if (data->pl_pos.player_angle_radian >= M_PI)
//         data->pl_pos.player_angle_radian -= 2 * M_PI;
// }
