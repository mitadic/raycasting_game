#include "../../includes/cub3d.h"

void	finish_reading_the_file(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

/* I think the check for "no line" is redundant, I think I checked for '< 3'
Captures the case where a line is shorter than max_x, stores ' '
 */
static int	extract_map_values(t_data *data, int fd, char *line)
{
	int	x;
	int	y;

	y = -1;
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

static int	is_empty_line(char *line)
{
	if (line[0] == '\n' && line[1] == 0)
		return (BOOL_YES);
	return (BOOL_NO);
}

/* Continue rotation while missing txt/rgb, or line == '\n' */
static int	extract_textures_and_rgbs(t_data *data, int fd, char **line)
{
	char	*minus_the_endline;

	while (((*line) != NULL && !is_textures_and_rgbs_complete(data)) || \
		is_empty_line(*line))
	{
		minus_the_endline = ft_strtrim(*line, "\n");
		// if (!minus_the_endline)
		// 	return (error(MALLOCFAIL, KO));
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

void	print_map(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	printf("max_x: %d, max_y: %d b4 printing\n", data->map.max_x, data->map.max_y);
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			printf("%c", data->map.vals[x][y]);
		}
		printf("\n");
	}
}

/* Finish extracting txt and rgbs first, then move on to the map */
int	extract_dotcub_values(t_data *data, int fd)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
		return(error(GNLFAIL, KO));
	if (extract_textures_and_rgbs(data, fd, &line) != OK || \
				extract_map_values(data, fd, line) != OK)
	{
		finish_reading_the_file(line, fd);
		return (KO);
	}
	print_map(data);
	return (OK);
}