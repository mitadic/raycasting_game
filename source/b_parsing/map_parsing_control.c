/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:14 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/05 14:03:21 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* A chain of returns brings us back out to main, only then do we free.
Any errors messages are printed on the spot, as soon as encountered. */


/* Validates and stores player position. No need for pl_pos.<c> to be init'd */
static int	locate_player(t_data *data)
{
	int y;
    int x;
	int	pl_pos_count;

    y = -1;
	pl_pos_count = 0;
    while (++y < data->map.max_y)
    {
        x = -1;
        while (++x < data->map.max_x)
		{
			if (ft_strchr(PLAYER_DIR, data->map.vals[x][y]))
			{
				data->pl_pos.x = x + 0.5;
				data->pl_pos.y = y + 0.5;
				pl_pos_count++;
			}
		}
    }
	if (pl_pos_count < 1)
		return (error(NOPL, KO));
	if (pl_pos_count > 1)
		return (error(TOOMANYPL, KO));
	return (OK);
}

/* Look for illegal symbols */
static int	validate_map_symbols(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (!ft_strchr(LEGAL_CHARS, data->map.vals[x][y]))
				return (error(ILLEGAL, KO));
		}
	}
	return (OK);
}

/* I think the check for "no line" is redundant, I think I checked for '< 3'
Captures the case where a line is shorter than max_x, stores ' '
 */
static int	extract_map_values(t_data *data, int fd)
{
	char *line;
	int	x;
	int	y;

	y = -1;
	line = get_next_line(fd);
	if (!line)
		return(error(BADMAP, KO));
	while (line)
	{
		y += 1;
		x = -1;
		while (++x < data->map.max_x)
		{
			if (x < (int)(ft_strlen(line) - ENDLINE))
				data->map.vals[x][y] = line[x];
			else
				data->map.vals[x][y] = ' ';
		}
		free(line);
		line = get_next_line(fd);
	}
	return (OK);
}

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

/* reopen map, populate char **map and read for invalidities */
int	validate_map(t_data *data, char *map_filename)
{
	int	fd;

	if (verify_filename(map_filename) != OK)
		return (KO);
	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	if (extract_map_values(data, fd) != OK)
		return (KO);
	if (close(fd) < 0)
		return (error(CANTCLOSE, KO));
	if (validate_map_symbols(data) != OK)
		return (KO);
	if (locate_player(data) != OK)
		return (KO);
	if (flood_fill(data) != OK)
		return (KO);
	return (OK);
}
