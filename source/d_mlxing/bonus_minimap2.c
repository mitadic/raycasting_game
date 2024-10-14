/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:07:54 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:17:26 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define SCALE_FACTOR 10
#define WALL_COLOR 0x669966 // Color for walls (greenish)
#define EMPTY_COLOR 0x11111 // Color for empty space (black)

void	put_pixel_to_image(t_minimap *minimap, int x, int y, int color)
{
	int	pixel_offset;

	if (x >= 0 && x < minimap->width && y >= 0 && y < minimap->height)
	{
		pixel_offset = (y * minimap->size_line) + (x * (minimap->bpp / 8));
		*(unsigned int *)(minimap->data + pixel_offset) = color;
	}
}

// Function to draw a square on the minimap image buffer
void	draw_square(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE_FACTOR)
	{
		j = 0;
		while (j < SCALE_FACTOR)
		{
			put_pixel_to_image(minimap, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
