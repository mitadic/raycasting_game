#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

int	start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != 0)
	{
		j = 0;
		while (set[j] != 0 && s1[i] != set[j])
			j++;
		if (s1[i] == set[j])
			i++;
		else
			break ;
	}
	return (i);
}

int	end(char const *s1, char const *set, int s1len)
{
	int	j;

	while (s1len > 0)
	{
		j = 0;
		while (set[j] != 0 && s1[s1len] != set[j])
			j++;
        if (s1len == 1 && s1[s1len] == set[j])
            return (s1len);
		if (s1[s1len] == set[j])
        {
			s1len--;
        }
		else
			break ;
	}
	return (s1len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		s1len;
	int		a;
	int		b;
	int		i;

	if (!s1 || !set)
		return (NULL);
	s1len = ft_strlen(s1);
	a = start(s1, set);
	b = end(s1, set, s1len);
	i = 0;
	while ((a + i) <= b && b != 0)
		i++;
	trimmed = malloc((i + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	i = 0;
	while ((a + i) <= b && b != 0)
	{
		trimmed[i] = s1[a + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}



int	main(void)
{
	char	*s1 = " \n  ";
	char	*set = " \t\v\f\r";
    char    *trimmed;

    trimmed = ft_strtrim(s1, set);
	printf("s1 trimmed is %s\n", trimmed);
    free(trimmed);
}

