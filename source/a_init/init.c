/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:25 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/07 13:55:10 by mitadic          ###   ########.fr       */
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

static void	init_map_struct(t_data *data)
{
	int	i;

	data->map.max_x = 0;
	data->map.max_y = 0;
	// data->map.vals = NULL;
	data->map.no = NULL;
	data->map.ea = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	i = -1;
	while (++i < 3)
	{
		data->map.ceiling[i] = -1;
		data->map.floor[i] = -1;
	}
}

/* control flow */
int	init(t_data *data, char *map_filename)
{
	init_map_struct(data);
	init_key_states(data);
	data->time.last_render.tv_sec = 0;

	data->img_buff.img = NULL;
	data->txt[0].img = NULL;
	data->txt[1].img = NULL;
	data->txt[2].img = NULL;
	data->txt[3].img = NULL;
	data->win = NULL;
	data->mlx = NULL;
	
	if (set_max_vector_values(data, map_filename) != OK || \
			malloc_for_map_vals(data) != OK || init_rays(data) != OK)
		return (KO);
	return (OK);
}
