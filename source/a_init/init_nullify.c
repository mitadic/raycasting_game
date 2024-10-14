/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nullify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:19:16 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/14 20:51:03 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_key_states(t_data *data)
{
	data->key_state.w = 0;
	data->key_state.a = 0;
	data->key_state.s = 0;
	data->key_state.d = 0;
	data->key_state.left = 0;
	data->key_state.right = 0;
}

static void init_mlx(t_data *data)
{
    data->img_buff.img = NULL;
	data->txt[0].img = NULL;
	data->txt[1].img = NULL;
	data->txt[2].img = NULL;
	data->txt[3].img = NULL;
	data->win = NULL;
	data->mlx = NULL;
}

static void	init_map_struct(t_data *data)
{
	int	i;

	data->map.max_x = 0;
	data->map.max_y = 0;
	data->map.vals = NULL;
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

static void set_rays_to_null(t_data *data)
{
    data->rays = NULL;
}

/* Control flow for setting to 'null' (invalid) all that needs setting */
void    init_nullify(t_data *data)
{
    init_key_states(data);
    init_map_struct(data);
    init_mlx(data);
    set_rays_to_null(data);
    data->time.last_render.tv_sec = 0;
}