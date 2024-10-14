/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_max_vector_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 00:46:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/12 01:18:24 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* If first non-space char is [0,1], we've started the map, return YES */
static int	is_map_start(char *line)
{
	int	i;

	i = -1;
	while (++i < (int)(ft_strlen(line) - ENDLINE))
	{
		if (ft_strchr(" ", line[i]))
			continue ;
		if (ft_strchr("01", line[i]))
			return (BOOL_YES);
		else
			return (BOOL_NO);
	}
	return (BOOL_NO);
}

/* Loop until map start, then loop through map characters */
static int	set_max_y_and_max_x(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (error("set_max_vectors: read nothing from file", KO));
	while (line)
	{
		if (is_map_start(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	data->map.max_x = ft_strlen(line) - ENDLINE;
	while (line)
	{
		data->map.max_y += 1;
		if ((int)(ft_strlen(line) - ENDLINE) > data->map.max_x)
			data->map.max_x = ft_strlen(line) - ENDLINE;
		free(line);
		line = get_next_line(fd);
	}
	return (OK);
}

/* open the map file for the sole purpose of finding max x and y values */
int	set_max_vector_values(t_data *data, char *map_filename)
{
	int	fd;

	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	set_max_y_and_max_x(data, fd);
	if (close(fd) < 0)
		return (error(CANTCLOSE, KO));
	if (data->map.max_x < 3 || data->map.max_y < 3)
		return (error(MAPTOOTINY, KO));
	return (OK);
}
