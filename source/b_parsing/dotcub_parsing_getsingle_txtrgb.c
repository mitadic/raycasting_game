#include "../../includes/cub3d.h"

static int	is_empty_line(char *line)
{
	if (line[0] == '\n' && line[1] == 0)
		return (BOOL_YES);
	return (BOOL_NO);
}

/* Do one of these things with the trimmed line, then go back to control:
    1. nothing (for newline)
    2. fetch RGB (for C, F)
    3. fetch texture (for NO, EA, SO, WE)
    4. complain (else)
Each scenario leaves <trimmed> freed below, nobody touches <line> */
void    extract_single_texture_or_rgb(t_data *data, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, WHITESPACES);
	// printf("len: %li, line: %strimmed: %s", ft_strlen(line), line, trimmed);
	if (!trimmed)
		return (void_error("malloc fail while extracting single txt/rgb"));
	if (is_empty_line(trimmed))
		;
	else if (!ft_strncmp(trimmed, "C ", 2))
        extract_rgb(data, trimmed, 'C');
	else if (!ft_strncmp(trimmed, "F ", 2))
        extract_rgb(data, trimmed, 'F');
	else if (!ft_strncmp(trimmed, "NO ", 3))
        extract_texture(data, trimmed, 'N');
    else if (!ft_strncmp(trimmed, "EA ", 3))
        extract_texture(data, trimmed, 'E');
	else if (!ft_strncmp(trimmed, "SO ", 3))
        extract_texture(data, trimmed, 'S');
	else if (!ft_strncmp(trimmed, "WE ", 3))
        extract_texture(data, trimmed, 'W');
	else
		printf("Unexpected specification in *.cub file, len: %ld, line: %s\n", ft_strlen(trimmed), trimmed);
	free(trimmed);
}