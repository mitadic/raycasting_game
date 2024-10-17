/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotcub_parsing_extraction_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:53:17 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/17 15:53:29 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int	extract_chars_from_line(t_data *data, int y, char **line)
{
	int	x;
	int	len;

	x = -1;
	len = calculate_line_len_without_final_endline(*line);
	while (++x < data->map.max_x)
	{
		if (x < len)
		{
			if (!ft_strchr(LEGAL_CHARS, (*line)[x]))
				return (KO);
			data->map.vals[x][y] = (*line)[x];
		}
		else
			data->map.vals[x][y] = ' ';
	}
	return (OK);
}
