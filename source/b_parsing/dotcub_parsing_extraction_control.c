/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotcub_parsing_extraction_control.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 01:19:59 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/17 15:43:33 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* If error found during reading a line, gotta finish reading */
void	finish_reading_the_file(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

/* Captures the case where a line is shorter than max_x, extracts ' ' */
static int	extract_map_values(t_data *data, int fd, char **line)
{
	int	y;
	int	map_end_flag;

	map_end_flag = BOOL_NO;
	y = -1;
	while (*line)
	{
		y += 1;
		if (extract_chars_from_line(data, y, line) != OK)
			return (error(ILLEGAL, KO));
		free(*line);
		*line = get_next_line(fd);
		if (y > 0 && *line && (*line)[0] == '\n')
			map_end_flag = BOOL_YES;
		if (map_end_flag && *line && (*line)[0] != '\n')
			return (error(DIRTYBOTTOM, KO));
	}
	return (OK);
}

static int	is_empty_line(char *line)
{
	if (line[0] == '\n' && line[1] == 0)
		return (BOOL_YES);
	return (BOOL_NO);
}

/* Continue rotation while not all txt+rgb complete, or line == '\n'
Then return and map extraction begins */
static int	extract_textures_and_rgbs(t_data *data, int fd, char **line)
{
	char	*minus_the_endline;

	while (((*line) != NULL && !is_textures_and_rgbs_extr_complete(data)) || \
		is_empty_line(*line))
	{
		minus_the_endline = ft_strtrim(*line, "\n");
		if (!minus_the_endline)
			return (error(MALLOCFAIL, KO));
		if (extract_single_texture_or_rgb(data, minus_the_endline) != OK)
		{
			free(minus_the_endline);
			return (KO);
		}
		free(minus_the_endline);
		free(*line);
		*line = get_next_line(fd);
	}
	return (OK);
}

/* Finish extracting txt and rgbs first, then move on to the map */
int	extract_dotcub_values(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (error(GNLFAIL, KO));
	if (extract_textures_and_rgbs(data, fd, &line) != OK || \
				extract_map_values(data, fd, &line) != OK)
	{
		finish_reading_the_file(line, fd);
		return (KO);
	}
	return (OK);
}
