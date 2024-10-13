/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:59:08 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:14:53 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_wall_height(t_rays *ray)
{
	ray->wall_height = (SCREEN_H / ray->distance);
}

/*intermediate hitpoint is where the ray first encounters a wall, 
it’s essential to perform further calculations to ensure that we find 
the true closest hitpoint for rendering or collision purposes*/
/*
if sideDist_X < sideDist_Y then the ray is rather vertical 
so we can take mapX as the x-value and need to calculate the y-value*/
/*
if sideDist_Y < sideDist_X then the ray is rather horizontal 
so we can take mapY as the x-value and need to calculate the x-value*/
/*in case sideDist_Y is infinite (no horizontal wall hits) 
we default to players y-position for y 
and only consider the x-direction for x*/

void	calculate_intermediate_hitpoint(t_rays *ray, t_pl_pos player)
{
	if (ray->sideDist_X < ray->sideDist_Y)
	{
		ray->intermediate_hit_x = ray->mapX;
		ray->intermediate_hit_y = player.y + ray->sideDist_X * ray->dir_y;
	}
	else
	{
		if (ray->sideDist_Y != INFINITY) 
		{
			ray->intermediate_hit_y = ray->mapY;
			ray->intermediate_hit_x = player.x 
				+ ray->sideDist_Y * ray->dir_x;
		}
		else 
		{
			ray->intermediate_hit_y = player.y;
			ray->intermediate_hit_x = player.x 
				+ ray->sideDist_X * ray->dir_x;
		}
	}
}
/*we check which wall is being hit(horizontal or vertical)*/
/* if (ray->stepX > 0) //ray goes to the right */
/*  if (ray->stepY > 0) //ray goes down */

void	assign_wall_color(t_rays *ray)
{
	if (ray->side == HORIZONTAL)
	{
		if (ray->stepX > 0)
			ray->wall_to_the = 'E'; 
		else
			ray->wall_to_the = 'W'; 
	}
	else
	{
		if (ray->stepY > 0)
			ray->wall_to_the = 'S'; 
		else
			ray->wall_to_the = 'N';
	}
}

void	adjust_for_fisheye_effect(t_pl_pos player, t_rays *ray, 
	float distance_without_correction)
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

/* we loop as long as there is no wall found */
/* if(ray->sideDist_X < ray->sideDist_Y) //ray is rather horizontal */
/* if(ray->sideDist_Y < ray->sideDist_X) //ray is rather vertical */
void	raycasting_loop(t_rays *ray, t_pl_pos player, char **map)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (ray->sideDist_X < ray->sideDist_Y)
		{
			ray->sideDist_X += ray->deltaDist_X;
			ray->mapX += ray->stepX;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->sideDist_Y += ray->deltaDist_Y;
			ray->mapY += ray->stepY;
			ray->side = VERTICAL;
		}
		if (map[ray->mapX][ray->mapY] == '1')
		{
			hit = 1;
			calculate_intermediate_hitpoint(ray, player);
		}
	}
}
