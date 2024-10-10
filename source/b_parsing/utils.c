#include "../../includes/cub3d.h"

void	free_strarr(char **strarr)
{
	int	i;

	i = -1;
	while (strarr[++i])
		free(strarr[i]);
	free(strarr[i]);
	free(strarr);
}

int get_strings_count(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		i++;
	return (i);
}

int	get_char_count(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return count;
}

int	atoi_cub3d_rgb(const char *nptr)
{
	long	l;
	int		minus;

	l = 0;
	minus = 1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == 32))
		nptr++;
	if (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			minus = -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		l += *nptr - 48;
		l *= 10;
		nptr++;
	}
	if (l / 10 * minus > INT_MAX || l / 10 * minus < INT_MIN)
		return (error("an RGB value going beyond 32 bits", -1));
	return (l / 10 * minus);
}

int	is_textures_and_rgbs_extr_complete(t_data *data)
{
	int	i;

	if (!data->map.no || !data->map.ea || !data->map.so || !data->map.we)
		return (BOOL_NO);
	i = -1;
	while (++i < 3)
	{
		if (data->map.ceiling[i] == -1 || data->map.floor[i] == -1)
			return (BOOL_NO);
	}
	return (BOOL_YES);
}
