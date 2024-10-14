/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:02:11 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/12 10:08:09 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* determines the float to use to scale & determine the x idx of texture */
float	get_the_float_component_of_hitp(t_data *data, int x)
{
	double	hp_float_x;
	double	hp_float_y;
	double	throwaway_int_x;
	double	throwaway_int_y;

	hp_float_x = modf(data->rays[x].hit_x, &throwaway_int_x);
	hp_float_y = modf(data->rays[x].hit_y, &throwaway_int_y);
	if (data->rays[x].side == VERTICAL)
		return (hp_float_x);
	return (hp_float_y);
}
