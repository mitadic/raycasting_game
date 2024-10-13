/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:10:30 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:18:51 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*if (data->pl_pos.player_angle_degree < -180)If turned L beyond W (-180 deg)*/
/* data->pl_pos.player_angle_degree += 360; // Switch to positive val */
void	rotate_left(t_data *data)
{
	data->pl_pos.player_angle_degree -= ROT_SPEED * 50;
	if (data->pl_pos.player_angle_degree < -180)
		data->pl_pos.player_angle_degree += 360;
}

/*if(data->pl_pos.player_angle_degree >= 180)
If turned R to W(beyond 179.999 deg)*/
/*         data->pl_pos.player_angle_degree -= 360; // Switch to negative val */
void	rotate_right(t_data *data)
{
	data->pl_pos.player_angle_degree += ROT_SPEED * 50;
	if (data->pl_pos.player_angle_degree >= 180)
		data->pl_pos.player_angle_degree -= 360;
}
