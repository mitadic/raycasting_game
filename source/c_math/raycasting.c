/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/20 18:45:24 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>


void adjust_for_fisheye_effect(t_pl_pos player, t_rays* ray, float distance_without_correction)
{
	float	angle_difference;
	float	correction_factor;

	angle_difference = player.player_angle_radian - ray->ray_angle;
	correction_factor = cos(angle_difference);
	if (fabs(correction_factor) < 0.01)
		ray->distance = distance_without_correction;
	else
		ray->distance = distance_without_correction * correction_factor;
}

void calculate_distance(t_rays *ray, t_pl_pos player, char **map)
{
	int hit = 0; 
	float distance;
	
	while(!hit) //loop as long as there is no wall found
	{
		if(ray->sideDist_X < ray->sideDist_Y) //ray is rather horizontal
		{
			ray->sideDist_X += ray->deltaDist_X;
			ray->mapX += ray->stepX;
			ray->side = HORIZONTAL;
			//printf("I calculate the intersections with horizontal lines\n");
		}
		else //ray is rather vertical
		{
			ray->sideDist_Y += ray->deltaDist_Y;
			ray->mapY += ray->stepY;
			ray->side = VERTICAL;
			//printf("I calculate the intersections with vertical lines\n");
		} 
		// Check if the current position is a wall
            if (map[ray->mapX][ray->mapY] == '1')
            {
                hit = 1;
				calculate_hit_point(ray, player);
                //printf("Hit a wall at (%d, %d)\n", ray->mapX, ray->mapY);
				//printf("\nHitpoint(%f, %f)\n", ray->hit_x, ray->hit_y);
		
            }
	}
	distance = sqrtf((pow(ray->intermediate_hit_x - player.x, 2.0)) + (pow(ray->intermediate_hit_y - player.y, 2.0)));
	// printf("calculated distance to wall(without correction): %f\n", distance);

	 //we need to substract deltaDist to get to the last hitpoint
	if (ray->side == HORIZONTAL) //ray is horizontal 
	{
		distance = (ray->sideDist_X - ray->deltaDist_X);
		// Calculate hitpoint on vertical wall
       	ray->hit_x = ray->mapX;
        ray->hit_y = player.y + (ray->mapX - player.x + (1 - ray->stepX) / 2) * ray->dir_y / ray->dir_x;
	}
  
	else //ray is vertical line
	{
		distance = (ray->sideDist_Y - ray->deltaDist_Y);
		ray->hit_y = ray->mapY;
        ray->hit_x = player.x + (ray->mapY - player.y + (1 - ray->stepY) / 2) * ray->dir_x / ray->dir_y;
	}
	adjust_for_fisheye_effect(player, ray, distance);
}
void calculate_delta_and_side(t_rays *ray, t_pl_pos player)
{
	//deltaDist_X and deltaDist_Y (meaning: distance from one axis to the next)
    if (ray->dir_x != 0)// avoid dividing by 0
        ray->deltaDist_X = ft_abs(1 / ray->dir_x);
    else
        ray->deltaDist_X = INFINITY; //very big value if 0
    if (ray->dir_y != 0)
        ray->deltaDist_Y = ft_abs(1 / ray->dir_y);
    else
    	ray->deltaDist_Y = INFINITY; 
		
    // printf("deltaDist_X is: %f\n", ray->deltaDist_X);
    // printf("deltaDist_Y is: %f\n", ray->deltaDist_Y);
    // printf("\n");
	
    // sideDist_X and sideDist_Y (meaning: distance from player to the axis)
    ray->mapX = (int)player.x;
    ray->mapY = (int)player.y;

	// printf("ray.mapX is: %d\n", ray->mapX);
    if (ray->dir_x > 0)
    {
        ray->stepX = 1;
        ray->sideDist_X = (ray->mapX + 1 - player.x) * ray->deltaDist_X;
    }
    else
    {
        ray->stepX = -1;
        ray->sideDist_X = (player.x - ray->mapX) * ray->deltaDist_X;
    }
    if (ray->dir_y > 0)
    {
        ray->stepY = 1;
        ray->sideDist_Y = (ray->mapY + 1 - player.y) * ray->deltaDist_Y;
    }
    else
    {
        ray->stepY = -1;
        ray->sideDist_Y = (player.y - ray->mapY) * ray->deltaDist_Y;
    }
	
    // printf("sideDist_X is: %f\n", ray->sideDist_X);
    // printf("sideDist_Y is: %f\n", ray->sideDist_Y);

	// printf("x player pos is at: %f\n", player.x);
	// printf("y player pos is at: %f\n", player.y);
}

int dda_algorithm(t_rays *ray, char **map, t_pl_pos player)
{

	calculate_delta_and_side(ray, player);
	calculate_distance(ray, player, map);
	assign_wall_color(ray);
	calculate_wall_height(ray);

    return (OK);
}


int calculate_vector(t_rays *ray)
{
	// 3. calculate the vector itself
	ray->dir_x = cos(ray->ray_angle);
	ray->dir_y = sin(ray->ray_angle);
	// printf("ray_dir_x is: %f\n",data->rays->dir_x);
	// printf("ray_dir_y is: %f\n",data->rays->dir_y);
	// printf("\n");

	return (OK);
}

int math(t_data *data)
{
	int	i;
	
	// 1. we determine the direction the player is looking (value is relative to the x-axis) in radian
	data->pl_pos.player_angle_radian = data->pl_pos.player_angle_degree * (M_PI / 180);
	i = -1;
	while(++i < SCREEN_W) //we assume that the number of rays is 320
	{
		// 2. calculate the ray angle for each ray (angle relative to player_angle)
		data->rays[i].ray_angle = data->pl_pos.player_angle_radian - FOV / 2 + i * (FOV / (SCREEN_W - 1));
		calculate_vector(&data->rays[i]);
		dda_algorithm(&data->rays[i], data->map.vals, data->pl_pos);
	}
	return(OK);
}


