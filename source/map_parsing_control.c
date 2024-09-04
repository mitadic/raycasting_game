#include "../includes/cub3d.h"

/* A chain of returns brings us back out to main, only then do we free.
Any errors messages are printed on the spot, as soon as encountered. */


/* Validates and stores player position. No need for pl_pos.<c> to be init'd */
static int	locate_player(t_data *data)
{
	int y;
    int x;
	int	pos_count;

    y = -1;
	pos_count = 0;
    while (++y < data->map.max_y)
    {
        x = -1;
        while (++x < data->map.max_x)
		{
			if (ft_strchr(PLAYER_DIR, data->map.vals[y][x]))
			{
				data->pl_pos.x = x + 0.5;
				data->pl_pos.y = y + 0.5;
				pos_count++;
			}
		}
    }
	if (pos_count < 1)
		return (error(NOPL, KO));
	if (pos_count > 1)
		return (error(TOOMANYPL, KO));
	return (OK);
}

/* Captures the case where a line is shorter than max_x, stores ' ' */
static int	go_through_this_line(t_data *data, int x, int y, char *line)
{
	int	line_len;

	line_len = ft_strlen(line) - ENDLINE;
	while (++x < data->map.max_x)
	{
		if (x < line_len)
		{
			if (!ft_strchr(LEGAL_CHARS, line[x]))
				return (error(ILLEGAL, KO));
			data->map.vals[y][x] = line[x];
		}
		else
			data->map.vals[y][x] = ' ';
	}
	return (OK);
}

static int	extract_map_values(t_data *data, int fd)
{
	char *line;
	int	x;
	int	y;

	y = -1;
	line = getnextline(fd);
	if (!line)
		return(error(BADMAP, KO));
	while (line)
	{
		y += 1;
		x = -1;
		if (go_through_this_line(data, x, y, line) != OK)
			return(KO);
		free(line);
		line = getnextline(fd);
	}
	return (OK);
}

/* reopen map, populate char **map and read for invalidities */
int	validate_map(t_data *data, char *map_filename)
{
	int	fd;

	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (error(CANTOPEN, KO));
	if (extract_map_values(data, fd) != OK)
		return (KO);
	close(fd);
	if (locate_player(data) != OK)
		return (KO);
	if (flood_fill(data) != OK)
		return (KO);
	return (OK);
}
