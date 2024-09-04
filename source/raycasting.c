/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/04 16:40:17 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>


void calculate_delta_and_side(t_rays *ray, t_pl_pos *player, char **map)
{
	//deltaDist_X and deltaDist_Y (meaning: distance from one axis to the next)

    // avoid dividing by 0
    if (ray->dir_x != 0)
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
    float sideDist_X;
    float sideDist_Y;

   

    int mapX = (int)player->x;
    int mapY = (int)player->y;

    int stepX;
    if (ray->dir_x > 0)
    {
        stepX = 1;
        sideDist_X = (mapX + 1 - player->x) * ray->deltaDist_X;
    }
    else
    {
        stepX = -1;
        sideDist_X = (player->x - mapX) * ray->deltaDist_X;
    }
 	int stepY;
    if (ray->dir_y > 0)
    {
        stepY = 1;
        sideDist_Y = (mapY + 1 - player->y) * ray->deltaDist_Y;
    }
    else
    {
        stepY = -1;
        sideDist_Y = (player->y - mapY) * ray->deltaDist_Y;
    }

    printf("sideDist_X is: %f\n", sideDist_X);
    printf("sideDist_Y is: %f\n", sideDist_Y);

	int hit = 0;

	while(!hit) //loop as long as there is no wall found
	{
		if(ray->sideDist_X < ray->deltaDist_Y) //rather horizontal
		{
			ray->sideDist_X += ray->deltaDist_X;
			mapX += stepX;
		}
		else //rather vertical
		{
			ray->sideDist_Y += ray->deltaDist_Y;
			mapY += stepY;
		}
		if(map[mapX][mapY] == '1')
		{
			hit =1;
		}
	}
	ray->distance = .... //to be continued
}
/* 
void calculate_distance(t_rays *ray, char **map, t_pl_pos *player)
{
	int hit = 0;

	while(!hit)
	{
		if(ray->sideDist_X < ray->deltaDist_Y) //meaning: rather horizontal
		{
			ray->sideDist_X += ray->deltaDist_X;
			mapX += stepX;
		}
		else
		{
			ray->sideDist_Y += ray->deltaDist_Y;
			mapY += stepY;
		}
	}
} */
int dda_algorithm(t_rays *ray, char **map, t_pl_pos *player)
{

	calculate_delta_and_side(ray, player, map);
/* 	calculate_distance(ray, map, player); */


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
	char **map = generate_bogus_map();
	data->pl_pos->x = 2; //hardcoded for now!!
	data->pl_pos->y = 2;
	
    if (!data || !data->map || !data->pl_pos || !data->rays) 
	{
        return (-1);
    }
	
	
	calculate_vector(data->rays); //only for the first ray for now
	dda_algorithm(data->rays, map, data->pl_pos); //only for the first ray for now
}