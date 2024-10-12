/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/12 17:27:23 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

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
/* to avoid skipping over hitpoints we need to 
substract deltaDist to get to the last hitpoint */
void	raycasting_loop(t_rays *ray, t_pl_pos player, char **map)
{
	int		hit;

	hit	= 0;
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
			calculate_hit_point(ray, player);
		}
	}
}

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

void	calculate_delta_and_side_2(t_rays *ray, t_pl_pos player)
{
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
}

/*	deltaDist: distance from one axis to the next
	sideDist: distance from the player to the next axis*/
void	calculate_delta_and_side_1(t_rays *ray, t_pl_pos player)
{
	if (ray->dir_x != 0)
		ray->deltaDist_X = ft_abs(1 / ray->dir_x);
	else
		ray->deltaDist_X = INFINITY;
	if (ray->dir_y != 0)
		ray->deltaDist_Y = ft_abs(1 / ray->dir_y);
	else
		ray->deltaDist_Y = INFINITY; 
	ray->mapX = (int)player.x;
	ray->mapY = (int)player.y;
	calculate_delta_and_side_2(ray, player);
}

int	dda_algorithm(t_rays *ray, char **map, t_pl_pos player)
{
	calculate_delta_and_side_1(ray, player);
	calculate_distance(ray, player, map);
	assign_wall_color(ray);
	calculate_wall_height(ray);
	return (OK);
}

/*calculate the vector*/
int	calculate_vector(t_rays *ray)
{
	ray->dir_x = cos(ray->ray_angle);
	ray->dir_y = sin(ray->ray_angle);
	return (OK);
}

/* 1. we determine the direction the player is looking */
/* (value is relative to the x-axis) in radian */
/* 	2. calculate the ray angle for each ray (angle relative to player_angle) */
int	math(t_data *data)
{
	int	i;

	i = -1;
	data->pl_pos.player_angle_radian = data->pl_pos.player_angle_degree 
		* (M_PI / 180);
	while (++i < SCREEN_W)
	{
		data->rays[i].ray_angle = data->pl_pos.player_angle_radian 
			- FOV / 2 + i * (FOV / (SCREEN_W - 1));
		calculate_vector(&data->rays[i]);
		dda_algorithm(&data->rays[i], data->map.vals, data->pl_pos);
	}
	return (OK);
}
