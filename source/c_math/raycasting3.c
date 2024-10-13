/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:45:14 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:15:10 by jasnguye         ###   ########.fr       */
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
		distance = (ray->sideDist_X - ray->deltaDist_X);
		ray->hit_x = ray->mapX;
		ray->hit_y = player.y + (ray->mapX - player.x + (1 - ray->stepX) / 2) 
			* ray->dir_y / ray->dir_x;
	}
	else
	{
		distance = (ray->sideDist_Y - ray->deltaDist_Y);
		ray->hit_y = ray->mapY;
		ray->hit_x = player.x + (ray->mapY - player.y + (1 - ray->stepY) / 2) 
			* ray->dir_x / ray->dir_y;
	}
	adjust_for_fisheye_effect(player, ray, distance);
}
