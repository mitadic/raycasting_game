/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:25 by mitadic           #+#    #+#             */
/*   Updated: 2024/11/06 20:19:45 by mitadic          ###   ########.fr       */
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

static int	init_rays(t_data *data)
{
	data->rays = malloc(sizeof(t_rays) * SCREEN_W);
	if (!data->rays)
		return (error(MALLOCFAIL, KO));
	return (OK);
}

static void	init_settings(t_data *data)
{
	data->settings.fov = M_PI / 3;
	data->settings.rot_speed = ROT_SPEED_FEED * MAX_FPS / PLAY_FPS;
	data->settings.mov_speed = MOV_SPEED_FEED * MAX_FPS / PLAY_FPS;
}

/* control flow */
int	init(t_data *data, char *map_filename)
{
	init_nullify(data);
	init_settings(data);
	if (set_max_vector_values(data, map_filename) != OK || \
			malloc_for_map_vals(data) != OK || init_rays(data) != OK)
		return (KO);
	if (BONUS_ENABLED)
		data->minimap.img = NULL;
	return (OK);
}
