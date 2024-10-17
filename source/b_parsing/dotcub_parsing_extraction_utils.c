#include "../../includes/cub3d.h"

int	calculate_line_len_without_final_endline(char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	if (line[len - 1] == '\n')
		len = len - ENDLINE;
	return (len);
}

/* If line ends with '\n', extract everything up to it, else all line 
If line is shorter than max_x (will never be longer), store ' ' up to max.x */
void	extract_chars_from_line(t_data *data, int y, char **line)
{
	int	x;
	int	len;

	x = -1;
	len = calculate_line_len_without_final_endline(*line);
	while (++x < data->map.max_x)
	{
		if (x < len)
			data->map.vals[x][y] = (*line)[x];
		else
			data->map.vals[x][y] = ' ';
	}
}