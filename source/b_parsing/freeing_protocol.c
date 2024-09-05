/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_protocol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:45 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/05 14:03:10 by mitadic          ###   ########.fr       */
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
        free(data->rays);
}