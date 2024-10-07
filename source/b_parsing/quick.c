#include <stdio.h>
#include "libft.h"

#define THIS_STR "    CEILING   255   ,  210,200     "

static void	free_strarr(char **strarr)
{
	int	i;

	i = -1;
	while (strarr[++i])
		free(strarr[i]);
	free(strarr[i]);
	free(strarr);
}

int	main(void)
{
	char	*trimmed;
	char	**chunk_with_spec;
	char	**res;
	int	i;

	trimmed = ft_strtrim(THIS_STR, " ");
	i = -1;
	if (!ft_strncmp(trimmed, "\n", 1) && ft_strlen(trimmed) == 1)
		free(trimmed);
	else if (
			!ft_strncmp(trimmed, "CEILING", 7) || \
			!ft_strncmp(trimmed, "FLOOR", 5))
	{
		res = ft_split(trimmed, ',');
		free(trimmed);
		if (!res)
			exit(1);
		trimmed = ft_strtrim(res[0], " ");
		if (!trimmed)
			exit(1);
		i = 0;
		chunk_with_spec = ft_split(trimmed, ' ');
		free(trimmed);
		printf("%s (len: %zu)\n", chunk_with_spec[1], ft_strlen(chunk_with_spec[1]));
		free_strarr(chunk_with_spec);
		while (res[++i])
		{
			trimmed = ft_strtrim(res[i], " ");
			printf("%s (len: %zu)\n", trimmed, ft_strlen(trimmed));
			free(trimmed);
		}
		free_strarr(res);
		if (i != 3)
			printf("Bad RGB values specification\n");
	}
	else if (
			!ft_strncmp(trimmed, "NO", 2) || \
			!ft_strncmp(trimmed, "EA", 2) || \
			!ft_strncmp(trimmed, "SO", 2) || \
			!ft_strncmp(trimmed, "WE", 2))
	{
		res = ft_split(trimmed, ' ');
		free(trimmed);
		if (!res)
			exit(1);
		while (res[++i])
		{
			printf("%s (len: %zu)\n", res[i], ft_strlen(res[i]));
			free(res[i]);
		}
		free(res);
		if (i != 2)
			printf("Bad texture specification\n");
	}
	else
		printf("Don't specify gibberish in my file\n");
	free (trimmed);
}
