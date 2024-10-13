/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:33:46 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:17:11 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define SCALE_FACTOR 10
#define WALL_COLOR 0x669966 // Color for walls (greenish)
#define EMPTY_COLOR 0x11111 // Color for empty space (black)

void	locate_player_on_minimap(t_data *data)
{
	data->minimap.player_mini_x = data->pl_pos.x * SCALE_FACTOR;
	data->minimap.player_mini_y = data->pl_pos.y * SCALE_FACTOR;
}

int	is_within_bounds(t_minimap *minimap, int x, int y)
{
	if (minimap->player_mini_x + x >= 0 
		&& minimap->player_mini_x + x < minimap->width 
		&& minimap->player_mini_y + y >= 0 
		&& minimap->player_mini_y + y < minimap->height)
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}

void	draw_player_dot(t_data *data, t_minimap *minimap)
{
	int	dot_size;
	int	y;
	int	x;

	dot_size = 4;
	y = -dot_size / 2;
	x = -dot_size / 2;
	locate_player_on_minimap(data);
	while (y <= dot_size / 2)
	{
		x = -dot_size / 2;
		while (x <= dot_size / 2)
		{
			if (is_within_bounds(minimap, x, y) == 1) 
			{
				put_pixel_to_image(minimap, data->minimap.player_mini_x 
					+ x, data->minimap.player_mini_y + y, 0xFF7C0);
			}
			x++;
		}
		y++;
	}
}

/*  scale map coordinates to minimap coordinates */
/*  draw the player's position on the minimap (as a dot) */
void	draw_minimap_on_image(t_data *data, t_minimap *minimap)
{
	int	mini_x;
	int	mini_y;
	int	x;
	int	y;

	(void)minimap;
	x = 0;
	y = 0;
	while (y < data->map.max_y) 
	{
		x = 0;
		while (x < data->map.max_x) 
		{
			mini_x = x * SCALE_FACTOR;
			mini_y = y * SCALE_FACTOR;
			if (data->map.vals[x][y] == '1') 
				draw_square(minimap, mini_x, mini_y, WALL_COLOR);
			else
				draw_square(minimap, mini_x, mini_y, EMPTY_COLOR);
			x++;
		}
		y++;
	}
	draw_player_dot(data, minimap);
}

void	initialize_minimap(t_data *data)
{
	int	minimap_width;
	int	minimap_height;

	if (BONUS_ENABLED) 
	{
		if (data->minimap.img != NULL)
		{
			mlx_destroy_image(data->mlx, data->minimap.img);
			data->minimap.img = NULL;
		}
	}
	if (data->map.max_x * SCALE_FACTOR > 200)
		data->minimap.width = 200;
	else
		data->minimap.width = data->map.max_x * SCALE_FACTOR;
	if (data->map.max_y * SCALE_FACTOR > 200)
		data->minimap.height = 200;
	else
		data->minimap.height = data->map.max_y * SCALE_FACTOR;
	data->minimap.img = mlx_new_image(data->mlx, data->minimap.width,
			data->minimap.height);
	data->minimap.data = mlx_get_data_addr(data->minimap.img,
			&data->minimap.bpp,
			&data->minimap.size_line, &data->minimap.endian);
}
