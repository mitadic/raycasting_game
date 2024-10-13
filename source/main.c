/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasnguye <jasnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:50 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/13 17:47:10 by jasnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error(PRINTUSAGE, 1));
	if (init(&data, argv[1]) != OK || parse_dotcub(&data, argv[1]) != OK)
		bail(&data, 2);
	go_mlxing(&data);
	purge(&data);
	return (OK);
}
