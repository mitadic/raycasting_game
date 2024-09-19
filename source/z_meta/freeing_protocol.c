/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamin <jamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/19 20:22:42 by jamin            ###   ########.fr       */
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

/* void    purge(t_data *data)
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
} */


void purge(t_data *data)
{
    free_map_vals(data);

    if (data->img_buff.img)
    {
        mlx_destroy_image(data->mlx, data->img_buff.img);
        data->img_buff.img = NULL; // Nullify after freeing to avoid double free
    }

    if (data->rays)
    {
        free(data->rays);
        data->rays = NULL;
    }

    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL; 
    }

    if (data->mlx)
    {
        mlx_destroy_display(data->mlx); //closing connection to physical screen
        free(data->mlx); // Free the mlx pointer itself after destroying the display
        data->mlx = NULL;
    }
}


