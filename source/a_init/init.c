/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:25 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/11 14:46:42 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* malloc for char **map using max_vector_values */
static int	malloc_for_map_vals(t_data *data)
{
	int	x;

	data->map.vals = malloc(sizeof(char *) * data->map.max_x);
	if (!data->map.vals)
		return (error(MALLOCFAIL, KO));
	x = -1;
	while (++x < data->map.max_x)
	{
		data->map.vals[x] = malloc(sizeof(char) * data->map.max_y);
		if (!data->map.vals[x])
			return (error(MALLOCFAIL, KO));
	}
	return (OK);
}

/* open the map file for the sole purpose of finding max x and y values */
static int	set_max_vector_values(t_data *data, char *map_filename)
{
	int	fd;
	char *line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	line = get_next_line(fd);
	data->map.max_x = ft_strlen(line) - ENDLINE;
	while (line)
	{
		data->map.max_y += 1;
		if ((int)(ft_strlen(line) - ENDLINE) > data->map.max_x)
			data->map.max_x = ft_strlen(line) - ENDLINE;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		return (error(CANTCLOSE, KO));
	if (data->map.max_x < 3 || data->map.max_y < 3)
		return (error(MAPTOOTINY, KO));
	return (OK);
}

int	init_rays(t_data *data)
{
	int	i;

	data->rays = malloc(sizeof(t_rays) * SCREEN_W);
	if (!data->rays)
		return (error(MALLOCFAIL, KO));
	i = -1;
	while (++i < SCREEN_W)
	{
		data->rays[i].side_delta_incr_X = 0;
		data->rays[i].side_delta_incr_Y = 0;
	}
	return (OK);
}

/* control flow */
int	init(t_data *data, char *map_filename)
{
	data->map.max_x = 0;
	data->map.max_y = 0;
	data->map.vals = NULL;
	if (set_max_vector_values(data, map_filename) != OK || \
			malloc_for_map_vals(data) != OK || init_rays(data) != OK)
		return (KO);
	return (OK);
}
