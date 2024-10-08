#include "../../includes/cub3d.h"

/* I think the check for "no line" is redundant, I think I checked for '< 3'
Captures the case where a line is shorter than max_x, stores ' '
 */
static void	extract_map_values(t_data *data, int fd, char *line)
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
}

static int	is_empty_line(char *line)
{
	if (line[0] == '\n' && line[1] == 0)
		return (BOOL_YES);
	return (BOOL_NO);
}

/* Continue rotation while missing txt/rgb, or line == '\n' */
static void	extract_textures_and_rgbs(t_data *data, int fd, char **line)
{
	char *minus_the_endline;

	while (((*line) != NULL && !is_textures_and_rgbs_complete(data)) || \
		is_empty_line(*line))
	{
		minus_the_endline = ft_strtrim(*line, "\n");
		free(*line);
		if (!minus_the_endline)
			void_error("malloc fail while trimming the endline");
		extract_single_texture_or_rgb(data, minus_the_endline);
		free(minus_the_endline);
		*line = get_next_line(fd);
	}
}

/* Finish extracting txt and rgbs first, then move on to the map
!!! NOT returning OK or KO while extracting (only if GNL fails),
because we gotta finish reading the file! */
int	extract_dotcub_values(t_data *data, int fd)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
		return(error(GNLFAIL, KO));
	extract_textures_and_rgbs(data, fd, &line);
	printf("done with rgb, now line is %s\n", line);
	extract_map_values(data, fd, line);
	return (OK);
}