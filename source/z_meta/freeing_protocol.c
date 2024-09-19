/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/18 15:29:01 by jasnguye         ###   ########.fr       */
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
    int i;

    free_map_vals(data);
    if (data->rays)
	{
		free(data->rays);
	}
    i = -1;
    while (++i < 4)
    {
        mlx_destroy_image(data->mlx, data->txt[i].img);
    }
	mlx_destroy_image(data->mlx, data->img_buff.img);
}