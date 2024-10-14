/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:22:07 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/14 12:54:13 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*step_x and step_y determine the direction in which the ray is moving*/
/*sideDist: distance from the player to the next axis*/
void	calculate_side(t_rays *ray, t_pl_pos player)
{
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = -1;
		ray->side_dist_x = (player.x - ray->map_x) * ray->delta_dist_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = -1;
		ray->side_dist_y = (player.y - ray->map_y) * ray->delta_dist_y;
	}
}

/*	deltaDist: distance from one axis to the next*/
void	calculate_delta(t_rays *ray, t_pl_pos player)
{
	if (ray->dir_x != 0)
		ray->delta_dist_x = ft_abs(1 / ray->dir_x);
	else
		ray->delta_dist_x = INFINITY;
	if (ray->dir_y != 0)
		ray->delta_dist_y = ft_abs(1 / ray->dir_y);
	else
		ray->delta_dist_y = INFINITY; 
	ray->map_x = (int)player.x;
	ray->map_y = (int)player.y;
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
			- data->settings.fov / 2 + i 
			* (data->settings.fov / (SCREEN_W - 1));
		calculate_vector(&data->rays[i]);
		dda_algorithm(&data->rays[i], data->map.vals, data->pl_pos);
	}
	return (OK);
}
