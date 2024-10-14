/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/14 20:41:15 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map_vals(t_data *data)
{
	int	x;

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

/* Destroy image buffer */
/* Destroy minimap image if BONUS is enabled */
/* Destroy texture images */
void	free_images(t_data *data)
{
	int	i;

	i = -1;
	if (data->img_buff.img)
	{
		mlx_destroy_image(data->mlx, data->img_buff.img);
		data->img_buff.img = NULL;
	}
	if (BONUS_ENABLED && data->minimap.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->minimap.img);
		data->minimap.img = NULL;
	}
	while (++i < 4)
	{
		if (data->txt[i].img)
			mlx_destroy_image(data->mlx, data->txt[i].img);
	}
}

/* Destroy window */
/* Destroy display and free MLX instance */
void	free_mlx_and_window(t_data *data)
{
	if ((*data).rays)
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
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	purge(t_data *data)
{
	free_map_vals(data);
	free_images(data);
	free_mlx_and_window(data);
}
