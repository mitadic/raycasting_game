/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_flood_sim.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:29 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/12 02:13:58 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Inside the loop, do 3 things:
	1. check if there's a field with 0, i.e. unflooded (== AIRPOCKETS)
	1. check if there's W(ater) in the very edgewalls (== LEAKYMAP)
	2. check if there's W(ater) touching ' ' (== UNRENDERABLE) */
static int	scan_for_dry_fields(t_data *data, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (map[x][y] == '0')
				return (error(AIRPOCKETS, KO));
			if ((y == 0 || y == data->map.max_y - 1 || \
					x == 0 || x == data->map.max_x - 1) \
					&& !ft_strchr(" 1", map[x][y]))
				return (error(LEAKYMAP, KO));
			if (map[x][y] == 'W' && (\
				(x > 0 && !ft_strchr("W1", map[x - 1][y])) || \
				(y > 0 && !ft_strchr("W1", map[x][y - 1])) || \
				(x < data->map.max_x - 1 && !ft_strchr("W1", map[x + 1][y])) || \
				(y < data->map.max_y - 1 && !ft_strchr("W1", map[x][y + 1]))))
				return (error(UNRENDERABLE, KO));
		}
	}
	return (OK);
}

/* recursive Paint fill tool, NESW: fill '0' with 'W'(ater) */
static void	flood_fields(t_data *data, char **map, int x, int y)
{
	if (map[x][y] == '0')
		map[x][y] = 'W';
	if (y > 0 && map[x][y - 1] == '0')
		flood_fields(data, map, x, y - 1);
	if (x < data->map.max_x - 1 && map[x + 1][y] == '0')
		flood_fields(data, map, x + 1, y);
	if (y < data->map.max_y - 1 && map[x][y + 1] == '0')
		flood_fields(data, map, x, y + 1);
	if (x > 0 && map[x - 1][y] == '0')
		flood_fields(data, map, x - 1, y);
}

/* Locate first available '0' to start the flood at.
At this point, we know that at the very least the player field exist,
which at this stage has been replaced with a '0' so we will find sth. */
static void	get_start_coords(t_data *data, char **map_copy, int (*coords)[2])
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (map_copy[x][y] == '0')
			{
				(*coords)[0] = x;
				(*coords)[1] = y;
				return ;
			}
		}
	}
}

/* get_start_coords and flood_fields guarranteed to be yielding. Go. */
int	flood_simulation(t_data *data, char **map_copy)
{
	int	start_coords[2];

	get_start_coords(data, map_copy, &start_coords);
	flood_fields(data, map_copy, start_coords[0], start_coords[1]);
	if (scan_for_dry_fields(data, map_copy) != OK)
		return (KO);
	return (OK);
}
