/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/19 12:41:29 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void    free_map_vals(t_data *data)
{
    int x;

    x = -1;
    if (!data->map.vals)
        return ;
    while (++x < data->map.max_x)
        free(data->map.vals[x]);
    free(data->map.vals);
}

void    purge(t_data *data)
{
    free_map_vals(data);
    if (data->rays)
	{
		free(data->rays);
	}
	if(data->img_buff.img)
	{
			mlx_destroy_image(data->mlx, data->img_buff.img);
	}
	if(data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
	}
}