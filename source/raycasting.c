/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/03 17:24:50 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

int calculate_distance(t_rays *ray)
{
    //deltaDist_X and deltaDist_Y (meaning: distance from one axis to the next)
    float deltaDist_X;
    float deltaDist_Y;

    // avoid dividing by 0
    if (ray->dir_x != 0)
        deltaDist_X = ft_abs(1 / ray->dir_x);
		
    else
        deltaDist_X = 1e30; //very big value if 0

    if (ray->dir_y != 0)
        deltaDist_Y = ft_abs(1 /ray->dir_y);
		
    else
        deltaDist_Y = 1e30; 

    printf("deltaDist_X is: %f\n", deltaDist_X);
    printf("deltaDist_Y is: %f\n", deltaDist_Y);
    printf("\n");

    // sideDist_X and sideDist_Y (meaning: distance from player to the axis)
    float sideDist_X;
    float sideDist_Y;
    float player_pos_x; //player position
    float player_pos_y;

    // Assuming the player position to be (3,3)
    player_pos_x = 3;
    player_pos_y = 3;

    int mapX = (int)player_pos_x;
    int mapY = (int)player_pos_y;

    int stepX;
    if (ray->dir_x > 0)
    {
        stepX = 1;
        sideDist_X = (mapX + 1 - player_pos_x) * deltaDist_X;
    }
    else
    {
        stepX = -1;
        sideDist_X = (player_pos_x - mapX) * deltaDist_X;
    }
 	int stepY;
    if (ray->dir_y > 0)
    {
        stepY = 1;
        sideDist_Y = (mapY + 1 - player_pos_y) * deltaDist_Y;
    }
    else
    {
        stepY = -1;
        sideDist_Y = (player_pos_y - mapY) * deltaDist_Y;
    }

    printf("sideDist_X is: %f\n", sideDist_X);
    printf("sideDist_Y is: %f\n", sideDist_Y);

    return 0;
}


int calculate_vector(t_rays *ray)
{
	// 1. we determine the direction the player is looking (value is relative to the x-axis) //this will need to be adjusted later
	float player_angle = 0;


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

    data->map = malloc(sizeof(t_map));
    data->pl_pos = malloc(sizeof(t_pl_pos));
    data->rays = malloc(sizeof(t_rays));

    if (!data || !data->map || !data->pl_pos || !data->rays) 
	{
        return (-1);
    }
	
	
	calculate_vector(data->rays); //only for the first ray for now
	calculate_distance(data->rays); //only for the first ray for now
}