/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/09 17:15:27 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>
#define SQUARE_SIZE 5
#define	MIN 0
#define	MAX 4

void calculate_hit_point(t_rays *ray, t_pl_pos player, float *hit_x, float *hit_y)
{
	if (ray->sideDist_X < ray->sideDist_Y) 
	{
        //  Strahl trifft vertikale Wand
        *hit_x = player.x + ray->sideDist_X * ray->dir_x;
        *hit_y = player.y + ray->sideDist_X * ray->dir_y;
    } else 
	{
        //  Strahl trifft horizontale Wand
        *hit_x = player.x + ray->sideDist_Y * ray->dir_x;
        *hit_y = player.y + ray->sideDist_Y * ray->dir_y;
    }
}
void calculate_distance(t_rays *ray, t_pl_pos player, char **map)
{
	int hit = 0; 
	float hit_x;
	float hit_y;
	while(!hit && ray->mapX >= MIN && ray->mapX < SQUARE_SIZE && ray->mapY >= MIN && ray->mapY < SQUARE_SIZE) //loop as long as there is no wall found
	{
		
		if(ray->sideDist_X < ray->sideDist_Y) //rather horizontal
		{
			ray->sideDist_X += ray->deltaDist_X;
			ray->mapX += ray->stepX;
		}
		else //rather vertical
		{
			ray->sideDist_Y += ray->deltaDist_Y;
			ray->mapY += ray->stepY;
		} 
		 printf("Ray position: mapX = %d, mapY = %d\n", ray->mapX, ray->mapY);

		// Check if the current position is a wall
        if (ray->mapX >= MIN && ray->mapX < SQUARE_SIZE && ray->mapY >= MIN && ray->mapY < SQUARE_SIZE)
        {
            if (map[ray->mapX][ray->mapY] == '1')
            {
                hit = 1;
				calculate_hit_point(ray, player, &hit_x, &hit_y);
                printf("Hit a wall at (%d, %d)\n", ray->mapX, ray->mapY);
				printf("Hitpoint(%f, %f)\n", hit_x, hit_y);
            }
        }
        else
        {
            // If out of bounds, exit loop to prevent endless loop
            printf("Out of bounds at (%d, %d)\n", ray->mapX, ray->mapY);
            break;
        }
	}
	
	ray->distance = sqrtf((pow(hit_x - player.x, 2.0)) + (pow(hit_y - player.y, 2.0)));
	printf("calculated distance to wall: %f\n", ray->distance);
}
void calculate_delta_and_side(t_rays *ray, t_pl_pos player, char **map)
{
	//deltaDist_X and deltaDist_Y (meaning: distance from one axis to the next)
    if (ray->dir_x != 0)// avoid dividing by 0
        ray->deltaDist_X = ft_abs(1 / ray->dir_x);
    else
        ray->deltaDist_X = 1e30; //very big value if 0
    if (ray->dir_y != 0)
        ray->deltaDist_Y = ft_abs(1 /ray->dir_y);
    else
    	ray->deltaDist_Y = 1e30; 
		
    printf("deltaDist_X is: %f\n", ray->deltaDist_X);
    printf("deltaDist_Y is: %f\n", ray->deltaDist_Y);
    printf("\n");
	
    // sideDist_X and sideDist_Y (meaning: distance from player to the axis)
    ray->mapX = (int)player.x;
    ray->mapY = (int)player.y;

    if (ray->dir_x > 0)
    {
        ray->stepX = 1;
        ray->sideDist_X= (ray->mapX + 1 - player.x) * ray->deltaDist_X;
    }
    else
    {
        ray->stepX = -1;
        ray->sideDist_X = (player.x - ray->mapX) * ray->deltaDist_X;
    }
 	int stepY;
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
    printf("sideDist_X is: %f\n", ray->sideDist_X);
    printf("sideDist_Y is: %f\n", ray->sideDist_Y);

	printf("x player pos is at: %f\n", player.x);
	printf("y player pos is at: %f\n", player.y);
}

int dda_algorithm(t_rays *ray, char **map, t_pl_pos player)
{

	calculate_delta_and_side(ray, player, map);
	calculate_distance(ray, player, map);


    return 0;
}


int calculate_vector(t_rays *ray)
{
	// 1. we determine the direction the player is looking (value is relative to the x-axis) //this will need to be adjusted later
	float player_angle = 0 * (M_PI /180); //hardcoded for now!!


	// 2. calculate the ray angle for each ray (angle relative to player_angle)
	float ray_angle;
/*	int i = 0;
 	while(i < 320) //we assume that the number of rays is 320
	{
		ray_angle = player_angle - FOV / 2 + i * (FOV / 320);
		i++;
	} */
	//here we ignore the loop and just calculate the ray_angle for the first ray
	ray_angle = player_angle - BOGENMASS / 2 + 0 * (BOGENMASS / 320);

	// 3. calculate the vector itself
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	printf("ray_dir_x is: %f\n",ray->dir_x);
	printf("ray_dir_y is: %f\n",ray->dir_y);
	printf("\n");

	return (0);
	
}

int main(void)
{

	t_data *data = malloc(sizeof(t_data));
    data->rays = malloc(sizeof(t_rays) * SCREEN_W);
	char **map = generate_bogus_map();
	data->pl_pos.x = 2.5; //hardcoded for now!!
	data->pl_pos.y = 2.5;
	
    if (!data || !data->rays) 
	{
        return (-1);
    }
	
	
	calculate_vector(data->rays); //only for the first ray for now
	dda_algorithm(data->rays, map, data->pl_pos); //only for the first ray for now
}