/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:45:14 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/14 12:38:33 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_distance(t_rays *ray, t_pl_pos player, char **map)
{
	float	distance;

	raycasting_loop(ray, player, map);
	distance = sqrtf((pow(ray->intermediate_hit_x - player.x, 2.0)) 
			+ (pow(ray->intermediate_hit_y - player.y, 2.0)));
	if (ray->side == HORIZONTAL)
	{
		distance = (ray->side_dist_x - ray->delta_dist_x);
		ray->hit_x = ray->map_x;
		ray->hit_y = player.y + (ray->map_x - player.x + (1 - ray->step_x) / 2) 
			* ray->dir_y / ray->dir_x;
	}
	else
	{
		distance = (ray->side_dist_y - ray->delta_dist_y);
		ray->hit_y = ray->map_y;
		ray->hit_x = player.x + (ray->map_y - player.y + (1 - ray->step_y) / 2) 
			* ray->dir_x / ray->dir_y;
	}
	adjust_for_fisheye_effect(player, ray, distance);
}
