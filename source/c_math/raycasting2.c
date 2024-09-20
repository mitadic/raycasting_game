/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:59:08 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/20 13:01:11 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>


void calculate_wall_height(t_rays *ray)
{
	ray->wall_height = SCREEN_H / ray->distance;
	// printf("calculated wall height: %f\n", ray->wall_height);
}

void calculate_hit_point(t_rays *ray, t_pl_pos player)
{
    if (ray->sideDist_X < ray->sideDist_Y)
    {
		// printf("in calculate hitpoint mapX is: %d\n", ray->mapX);
        // Ray hits vertical wall (x-boundary first)
        ray->hit_x = ray->mapX; // X-position of the wall (since it's vertical)
        ray->hit_y = player.y + ray->sideDist_X * ray->dir_y; // Calculate Y-position
    }
    else
    {
        // Ray hits horizontal wall (y-boundary first)
        if (ray->sideDist_Y != INFINITY) {
            ray->hit_y = ray->mapY; // Y-position of the wall (since it's horizontal)
            ray->hit_x = player.x + ray->sideDist_Y * ray->dir_x; // Calculate X-position
        } else {
            // In case sideDist_Y is infinity (no horizontal wall hit)
            ray->hit_y = player.y; // Default to player's y-position
            ray->hit_x = player.x + ray->sideDist_X * ray->dir_x; // Only consider X direction
        }
    }
}

void assign_wall_color(t_rays *ray)
{
    // check which side the ray is hitting
    if (ray->side == 0) // ray is hitting a vertical wall
    {
        if (ray->stepX > 0) //ray goes to the right
            ray->wall_to_the = 'E'; 
        else //ray goes to the left
            ray->wall_to_the = 'W'; 
    }
    else // ray is hitting a horizontal wall
    {
        if (ray->stepY > 0) //ray goes down
            ray->wall_to_the = 'S'; 
        else //ray goes up
            ray->wall_to_the = 'N'; 
    }
}