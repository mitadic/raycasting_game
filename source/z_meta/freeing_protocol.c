/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/10 13:11:10 by jasnguye         ###   ########.fr       */
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
	free(data->map.no);
	free(data->map.ea);
	free(data->map.so);
	free(data->map.we);
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

//new purge function
void purge(t_data *data)
{
	int i;

	free_map_vals(data);

	if (data->img_buff.img)
	{
		mlx_destroy_image(data->mlx, data->img_buff.img);
		data->img_buff.img = NULL; // Nullify after freeing to avoid double free
	}
/* 	if(BONUS && data->minimap.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->minimap.img);
		data->minimap.img = NULL;
	} */

	i = -1;
	while (++i < 4)
	{
		if (data->txt[i].img)
			mlx_destroy_image(data->mlx, data->txt[i].img);
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


