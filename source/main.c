/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:50 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/13 15:02:27 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data  data;

	if (argc != 2)
		return (error(PRINTUSAGE, 1));
	if (init(&data, argv[1]) != OK || validate_map(&data, argv[1]) != OK)
		bail(&data, 2);
	go_mlxing(&data); // makes call to math(data) for all rays
	purge(&data);
	return (OK);
}
