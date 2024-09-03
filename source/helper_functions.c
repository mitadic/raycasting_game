/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:24:02 by jasnguye          #+#    #+#             */
/*   Updated: 2024/09/03 17:24:19 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

float ft_abs(float number)
{
	if(number < 0)
	{
		return(-number);
	}
	else
	{
		return(number);
	}
}
