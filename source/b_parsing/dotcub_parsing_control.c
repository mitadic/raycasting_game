/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotcub_parsing_control.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:14 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/07 15:52:06 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* A chain of returns brings us back out to main, only then do we free.
Any error messages are printed on the spot, as soon as encountered. */

/* ensure an early exit for filenames too short or with incorrect suffix */
static int	verify_filename(char *map_filename)
{
	int	len;

	len = ft_strlen(map_filename);
	if (len < 5)
		return (error(PRINTUSAGE, KO));
	if (ft_strncmp(".cub", &map_filename[len - 4], 4) != OK)
		return (error(BADSUFF, KO));
	return (OK);
}

/* reopen dotcub, extract values, verify completeness, read for invalidities,
validate player location, and finally validate map via flood fill */
int	parse_dotcub(t_data *data, char *map_filename)
{
	int	fd;

	if (verify_filename(map_filename) != OK)
		return (KO);
	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	if (extract_dotcub_values(data, fd) != OK)
		return (KO);
	if (close(fd) < 0)
		return (error(CANTCLOSE, KO));
	if (val_init_map(data) != OK || val_init_txtrgb(data) != OK)
		return (KO);
	if (flood_fill(data) != OK)
		return (KO);
	return (OK); 
}
