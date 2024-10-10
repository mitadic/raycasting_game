/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:25 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/10 14:21:51 by jasnguye         ###   ########.fr       */
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
	data->rays = malloc(sizeof(t_rays) * SCREEN_W);
	if (!data->rays)
		return (error(MALLOCFAIL, KO));

	return (OK);
}

static void	init_key_states(t_data *data)
{
	data->key_state.w = 0;
	data->key_state.a = 0;
	data->key_state.s = 0;
	data->key_state.d = 0;
	data->key_state.left = 0;
	data->key_state.right = 0;
}

/* control flow */
int	init(t_data *data, char *map_filename)
{
	data->map.max_x = 0;
	data->map.max_y = 0;
	data->map.vals = NULL;
	data->win = NULL;
	data->mlx = NULL;

data->pl_pos.player_angle_degree = 0.0; // Initialize player angle

	init_key_states(data);
	data->time.last_render.tv_sec = 0;
	if (set_max_vector_values(data, map_filename) != OK || \
			malloc_for_map_vals(data) != OK || init_rays(data) != OK ||\
			init_textures(data, map_filename) != OK)
		return (KO);
	if(BONUS)
	{
		data->minimap.img = NULL;
	}
	return (OK);
}
