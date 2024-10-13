/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:15:26 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*stepX and stepY determine the direction in which the ray is moving*/
/*sideDist: distance from the player to the next axis*/
void	calculate_side(t_rays *ray, t_pl_pos player)
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

/*	deltaDist: distance from one axis to the next*/
void	calculate_delta(t_rays *ray, t_pl_pos player)
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
}

int	dda_algorithm(t_rays *ray, char **map, t_pl_pos player)
{
	calculate_delta(ray, player);
	calculate_side(ray, player);
	calculate_distance(ray, player, map);
	assign_wall_color(ray);
	calculate_wall_height(ray);
	return (OK);
}

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
