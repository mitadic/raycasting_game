/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:33:46 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/08 17:42:21 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_SIZE 180 // Size of the minimap
#define SCALE_FACTOR 10
#define WALL_COLOR 0x669966 // Color for walls (greenish)
#define EMPTY_COLOR 0x11111 // Color for empty space (black)

void put_pixel_to_image(t_minimap *minimap, int x, int y, int color)
{
    if (x >= 0 && x < minimap->width && y >= 0 && y < minimap->height)
    {
        int pixel_offset = (y * minimap->size_line) + (x * (minimap->bpp / 8));
        *(unsigned int *)(minimap->data + pixel_offset) = color;
    }
}

// Function to draw a square on the minimap image buffer
void draw_square(t_minimap *minimap, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            put_pixel_to_image(minimap, x + i, y + j, color);
        }
    }
}




/* void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color) {
    int i;
    int j;

	i = 0;
	j = 0;
    // Loop through each pixel in the square
    while (i < size) 
	{
        while (j < size) 
		{
            // Draw the pixel at the calculated position
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
			j++;
        }
		i++;
    }
} */


/* 
void clear_minimap_area(t_data *data)
{
	int x = 0;
	int y = 0;

	while(y < data->map.max_y)
	{
		x = 0;
		while(x < data->map.max_x)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, EMPTY_COLOR);
			x++;
		}
		y++;
	}
} */

void draw_player_dot(t_data *data, t_minimap *minimap, int player_mini_x, int player_mini_y)
{
	(void)data;
	int dot_size = 4;
	int y = -dot_size / 2;
	int x = -dot_size / 2;
	while(y <= dot_size/2)
	{ 
		x = -dot_size / 2; // Reset x for each row of the dot
		while(x <= dot_size/2)
		{

            // Ensure the pixel is within the minimap bounds before drawing
            if (player_mini_x + x >= 0 && player_mini_x + x < minimap->width && player_mini_y + y >= 0 && player_mini_y + y < minimap->height) 
            {
                put_pixel_to_image(minimap, player_mini_x + x, player_mini_y + y, 0xFF7C0);
            }
			x++;
		}
		y++;
	}
}
void draw_minimap_on_image(t_data *data, t_minimap *minimap) 
{
    int mini_x, mini_y;

    // clear the minimap area before drawing // not implemented yet
  // clear_minimap_area(data);

	(void)minimap;
	int x = 0; // to iterate through the actual map
	int y = 0;


	while(y < data->map.max_y) 
	{
		x = 0;
        while (x < data->map.max_x) 
		{
            // scale map coordinates to minimap coordinates
            mini_x = x * SCALE_FACTOR;
            mini_y = y * SCALE_FACTOR;

            // check for wall or empty space
            if (data->map.vals[x][y] == '1') 
			{
                // draw wall on minimap
                draw_square(minimap, mini_x, mini_y, SCALE_FACTOR, WALL_COLOR);
            } 
			else 
			{
                // draw empty space on minimap
                draw_square(minimap, mini_x, mini_y, SCALE_FACTOR, EMPTY_COLOR);
            }
			x++;
        }
		y++;
    }

    // draw the player's position on the minimap (as a dot)

    int player_mini_x = data->pl_pos.x * SCALE_FACTOR;
    int player_mini_y = data->pl_pos.y * SCALE_FACTOR;
	draw_player_dot(data, minimap, player_mini_x, player_mini_y);
    //put_pixel_to_image(&data->minimap, player_mini_x, player_mini_y, 0xFF7C00); 

   // draw_square(minimap, (int)data->pl_pos.x * SCALE_FACTOR, data->pl_pos.y * SCALE_FACTOR, SCALE_FACTOR, 0xff7c00); //orange square for player
}


void initialize_minimap(t_data *data)
{
	
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
    data->minimap.data = mlx_get_data_addr(data->minimap.img, &data->minimap.bpp,
            &data->minimap.size_line, &data->minimap.endian);
    data->minimap.width = MINIMAP_SIZE;
    data->minimap.height = MINIMAP_SIZE;
	
}

//don't forget to add at the end:
///extra rule for BONUS in MAKEfile needed!!!!