/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/02 18:03:57 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

int calculate_vectors(/* t_data *data, t_pl_pos *player */void)
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
	float ray_dir_x;
	float ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	printf("ray_dir_x is: %f\n",ray_dir_x);
	printf("ray_dir_y is: %f\n",ray_dir_y);

	return (0);
	
}


int main(void)
{
	calculate_vectors();
}