#include "../../includes/cub3d.h"

// static int	is_empty_line(char *line)
// {
// 	if (line[0] == '\n' && line[1] == 0)
// 		return (BOOL_YES);
// 	return (BOOL_NO);
// }

/* Do one of these things with the trimmed line, then go back to control:
    1. nothing (for newline)
    2. fetch RGB (for C, F)
    3. fetch texture (for NO, EA, SO, WE)
    4. complain (else), though currently this also catches malloc fail of trim
Each scenario leaves <trimmed> freed below, nobody touches <line> */
int    extract_single_texture_or_rgb(t_data *data, char *line)
{
	char	*trimmed;
	int		qc_flag;

	trimmed = ft_strtrim(line, WHITESPACES);
	if (trimmed && trimmed[0] == 0)
		qc_flag = OK;
	else if (!ft_strncmp(trimmed, "C ", 2))
        qc_flag = extract_rgb(data, trimmed, 'C');
	else if (!ft_strncmp(trimmed, "F ", 2))
        qc_flag = extract_rgb(data, trimmed, 'F');
	else if (!ft_strncmp(trimmed, "NO ", 3))
        qc_flag = extract_texture(data, trimmed, 'N');
    else if (!ft_strncmp(trimmed, "EA ", 3))
        qc_flag = extract_texture(data, trimmed, 'E');
	else if (!ft_strncmp(trimmed, "SO ", 3))
        qc_flag = extract_texture(data, trimmed, 'S');
	else if (!ft_strncmp(trimmed, "WE ", 3))
        qc_flag = extract_texture(data, trimmed, 'W');
	else
		qc_flag = (error(BADSPEC, KO));
	free(trimmed);
	return (qc_flag);
}
