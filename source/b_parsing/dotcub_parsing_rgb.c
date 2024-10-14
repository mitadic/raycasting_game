/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotcub_parsing_rgb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 01:20:32 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/12 01:51:42 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* if bad, return and leave the value as initialized to -1, validate later */
static int	store_one_of_rgb(t_data *data, char *nptr, char where, int which)
{
	int	i;

	if (ft_strlen(nptr) > 3)
		return (error(RGBTOOLONG, KO));
	i = -1;
	while (++i < (int)ft_strlen(nptr) || (int)ft_strlen(nptr) == 0)
	{
		if (nptr[i] == 0 || !ft_isdigit(nptr[i]))
			return (error(NONDIGIT, KO));
	}
	if (where == 'C')
		data->map.ceiling[which] = atoi_cub3d_rgb(nptr);
	else if (where == 'F')
		data->map.floor[which] = atoi_cub3d_rgb(nptr);
	return (OK);
}

/* This shouldn't need string count of rgbs verification, we counted the ',' */
static int	extract_the_gb(t_data *data, char **rgbs, char where)
{
	char	*trimmed;
	int		i;
	int		qc_flag;

	i = 0;
	while (rgbs[++i])
	{
		trimmed = ft_strtrim(rgbs[i], WHITESPACES);
		if (!trimmed)
			return (error(MALLOCFAIL_GB, KO));
		qc_flag = store_one_of_rgb(data, trimmed, where, i);
		free(trimmed);
		if (qc_flag == KO)
			break ;
	}
	return (qc_flag);
}

static int	extract_the_r(t_data *data, char *left_of_comma, char where)
{
	char	*trimmed;
	char	**identifier_and_r;
	int		qc_flag;

	trimmed = ft_strtrim(left_of_comma, WHITESPACES);
	if (!trimmed)
		return (error(MALLOCFAIL_R, KO));
	identifier_and_r = ft_split(trimmed, ' ');
	free(trimmed);
	if (!identifier_and_r)
		return (error(MALLOCFAIL_R, KO));
	if (get_strings_count(identifier_and_r) != 2)
	{
		free_strarr(identifier_and_r);
		return (error(GENERICBAD_RGB, KO));
	}
	trimmed = ft_strtrim(identifier_and_r[1], WHITESPACES);
	free_strarr(identifier_and_r);
	if (!trimmed)
		return (error(MALLOCFAIL_R, KO));
	qc_flag = store_one_of_rgb(data, trimmed, where, 0);
	free(trimmed);
	return (qc_flag);
}

/* Return KO if:
	1. Not two commas
	2. Already initialized (C if C, or F if F)
	3. ft_split fail
	4. ft_split didn't return 3 strings exactly
	5. extracting the r or gb has failed otherwise
	*/
int	extract_rgb(t_data *data, char *line, char where)
{
	char	**rgbs;

	if (get_char_count(line, ',') != 2)
		return (error(NOTTWOCOMMAS, KO));
	if ((where == 'C' && data->map.ceiling[0] != -1) || \
		(where == 'F' && data->map.floor[0] != -1))
		return (error(ALREADYINIT_RGB, KO));
	rgbs = ft_split(line, ',');
	if (!rgbs)
		return (error(MALLOCFAIL_RGB, KO));
	if (get_strings_count(rgbs) != 3)
	{
		free_strarr(rgbs);
		return (error(NOTTHREE_RGB, KO));
	}
	if (extract_the_r(data, rgbs[0], where) != OK || \
		extract_the_gb(data, rgbs, where) != OK)
	{
		free_strarr(rgbs);
		return (KO);
	}
	free_strarr(rgbs);
	return (OK);
}
