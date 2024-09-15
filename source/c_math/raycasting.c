/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/13 13:22:58 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>


void calculate_wall_height(t_rays *ray)
{
	ray->wall_height = SCREEN_H / ray->distance;
	printf("calculated wall height: %f\n", ray->wall_height);
}

// void calculate_hit_point(t_rays *ray, t_pl_pos player, float *hit_x, float *hit_y)
// {
// 	if (ray->sideDist_X < ray->sideDist_Y) 
// 	{
//         //  Strahl trifft vertikale Wand
//         *hit_x = ray->mapX;//player.x + ray->sideDist_X * ray->dir_x;
//         *hit_y =  player.y + (ray->sideDist_X - ray->deltaDist_X) * ray->dir_y; //player.y + ray->sideDist_X * ray->dir_y;
//     } else 
// 	{
//         //  Strahl trifft horizontale Wand
//         *hit_x = player.x + (ray->sideDist_Y - ray->deltaDist_Y) * ray->dir_x;//player.x + ray->sideDist_Y * ray->dir_x;
//         *hit_y = ray->mapY;//player.y + ray->sideDist_Y * ray->dir_y;
//     }

// if (ray->sideDist_X < ray->sideDist_Y) 
// 	{
//         //  Strahl trifft vertikale Wand
//         *hit_x = player.x + ray->sideDist_X * ray->dir_x;
//         *hit_y =  player.y + ray->sideDist_X * ray->dir_y;
//     } else 
// 	{
//         //  Strahl trifft horizontale Wand
//         *hit_x = player.x + ray->sideDist_Y * ray->dir_x;
//         *hit_y = player.y + ray->sideDist_Y * ray->dir_y;
//     }


// }
void calculate_hit_point(t_rays *ray, t_pl_pos player, float *hit_x, float *hit_y)
{
    if (ray->sideDist_X < ray->sideDist_Y)
    {
		// printf("in calculate hitpoint mapX is: %d\n", ray->mapX);
        // Ray hits vertical wall (x-boundary first)
        *hit_x = ray->mapX; // X-position of the wall (since it's vertical)
        *hit_y = player.y + ray->sideDist_X * ray->dir_y; // Calculate Y-position
    }
    else
    {
        // Ray hits horizontal wall (y-boundary first)
        if (ray->sideDist_Y != INFINITY) {
            *hit_y = ray->mapY; // Y-position of the wall (since it's horizontal)
            *hit_x = player.x + ray->sideDist_Y * ray->dir_x; // Calculate X-position
        } else {
            // In case sideDist_Y is infinity (no horizontal wall hit)
            *hit_y = player.y; // Default to player's y-position
            *hit_x = player.x + ray->sideDist_X * ray->dir_x; // Only consider X direction
        }
    }
}




void adjust_map_coords_for_index(t_rays *ray, t_pl_pos player)
{
	// printf("player angle is: %f\n", player.player_angle_degree);
	if (player.player_angle_degree < -90 || player.player_angle_degree > 90)
	{
		ray->mapX += 1;
	}


	if (player.player_angle_degree < 0)
	{
		ray->mapY += 1;
	}

}

// float normalize_angle(float angle)
// {
//     while (angle < -M_PI) angle += M_PI;
//     while (angle > M_PI) angle -= M_PI;
//     return angle;
// }

void adjust_for_fisheye_effect(t_pl_pos player, t_rays* ray, float distance_without_correction)
{
	float	angle_difference;
	float	correction_factor;

	angle_difference = player.player_angle_radian - ray->ray_angle;
	correction_factor = cos(angle_difference / M_PI);
	if (fabs(correction_factor) < 0.01)
		ray->distance = distance_without_correction;
	else
		ray->distance = distance_without_correction * correction_factor;
	// MILOS: diagnostics
	// if ((ray->ray_angle > -0.01 && ray->ray_angle < 0.01) || ray->ray_angle > 0.52)
	// {
	// 	printf("calculated distance to wall(without correction): %f\n", distance_without_correction);
	// 	printf("player_angle_radian is %f, ray_angle is %f, correction factor is %f\n", player.player_angle_radian, ray->ray_angle, correction_factor);
	// 	printf("corrected distance: %f\n", ray->distance);
	// }
}

void calculate_distance(t_rays *ray, t_pl_pos player, char **map)
{
	int hit = 0; 
	float hit_x = 0.0;
	float hit_y = 0.0;
	float distance;
	// (void)data;
	while(!hit) //loop as long as there is no wall found
	{
		
		if(ray->sideDist_X < ray->sideDist_Y) //rather horizontal
		{
			if (!ray->side_delta_incr_X)
				ray->side_delta_incr_X = ray->sideDist_X;
			ray->side_delta_incr_X += ray->deltaDist_X;
			ray->mapX += ray->stepX;
			// printf("in calculate distance mapX is: %d\n", ray->mapX);
		}
		else //rather vertical
		{
			if (!ray->side_delta_incr_Y)
				ray->side_delta_incr_Y = ray->sideDist_Y;
			ray->side_delta_incr_Y += ray->deltaDist_Y;
			ray->mapY += ray->stepY;
		} 
		//  printf("Ray position: mapX = %d, mapY = %d\n", ray->mapX, ray->mapY);

		// Check if the current position is a wall
       
            if (map[ray->mapX][ray->mapY] == '1')
            {
                hit = 1;
				adjust_map_coords_for_index(ray, player);
				calculate_hit_point(ray, player, &hit_x, &hit_y);
                // printf("Hit a wall at (%d, %d)\n", ray->mapX, ray->mapY);
				// printf("\nHitpoint(%f, %f)\n", hit_x, hit_y);
		
            }
	}
	// ray->distance = sqrtf((pow(hit_x - player.x, 2.0)) + (pow(hit_y - player.y, 2.0)));
	distance = sqrtf((pow(hit_x - player.x, 2.0)) + (pow(hit_y - player.y, 2.0)));
	// printf("calculated distance to wall(without correction): %f\n", distance);
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
	// milos: suspend the below for now
	// jasmin: here we ignore the loop and just calculate the ray_angle for the first ray
	// data->rays->ray_angle = data->pl_pos.player_angle_radian - BOGENMASS / 2 + 160 * (BOGENMASS / 320);

	return (OK);
}

int math(t_data *data)
{
	int	i;

	// 1. we determine the direction the player is looking (value is relative to the x-axis) //this will need to be adjusted later
	data->pl_pos.player_angle_degree = 150;
	data->pl_pos.player_angle_radian = data->pl_pos.player_angle_degree * (M_PI / 180); //hardcoded for now!!
	i = -1;
	while(++i < SCREEN_W) //we assume that the number of rays is 320
	{
		// 2. calculate the ray angle for each ray (angle relative to player_angle)
		data->rays[i].ray_angle = data->pl_pos.player_angle_radian - FOV / 2 + i * (FOV / (SCREEN_W - 1));
		calculate_vector(&data->rays[i]); //only for the first ray for now
		dda_algorithm(&data->rays[i], data->map.vals, data->pl_pos); //only for the first ray for now
	}
	return(OK);
}