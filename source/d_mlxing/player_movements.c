#include "../../includes/cub3d.h"


#define WALL '1'
#define PLAYER_RADIUS 0.1 // Small radius for the player to avoid "corner sticking"
#define COLLISION_BUFFER 0.2 //can be modified


// Function to check if a position is a wall
/* int is_wall(float new_x_pos, float new_y_pos, t_data *data)
{
    int mapX = (int)new_x_pos;
    int mapY = (int)new_y_pos;


	return(data->map.vals[mapX][mapY] == WALL);
	

}  */

int is_wall(float new_x_pos, float new_y_pos, t_data *data)
{
    // Convert player's position to map coordinates
    int mapX = (int)new_x_pos;
    int mapY = (int)new_y_pos;

    // Calculate buffered positions
    float x_left = new_x_pos - COLLISION_BUFFER;
    float x_right = new_x_pos + COLLISION_BUFFER;
    float y_up = new_y_pos - COLLISION_BUFFER;
    float y_down = new_y_pos + COLLISION_BUFFER;

    // Convert buffered positions to map coordinates
    int mapX_left = (int)x_left;
    int mapX_right = (int)x_right;
    int mapY_up = (int)y_up;
    int mapY_down = (int)y_down;

    // Check if any of these positions hit a wall
    if (data->map.vals[mapX][mapY] == WALL ||  // Current position
        data->map.vals[mapX_left][mapY] == WALL ||  // Left buffer
        data->map.vals[mapX_right][mapY] == WALL ||  // Right buffer
        data->map.vals[mapX][mapY_up] == WALL ||  // Up buffer
        data->map.vals[mapX][mapY_down] == WALL)  // Down buffer
    {
        return 1;  // Wall detected
    }

    return 0;  // No wall detected
} 

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

