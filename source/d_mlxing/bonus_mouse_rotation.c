/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:12:50 by jasnguye          #+#    #+#             */
/*   Updated: 2024/10/13 20:18:06 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse_scroll_up(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)x;
	(void)y;
	if (!data)
	{
		printf("data uninitialized\n");
		return (1);
	}
	if (button == 4)
	{
		rotate_left(data);
	}
	return (0);
}

int	handle_mouse_scroll_down(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)x;
	(void)y;
	if (!data)
	{
		printf("data uninitialized\n");
		return (1);
	}
	if (button == 5)
	{
		rotate_right(data);
	}
	return (0);
}
