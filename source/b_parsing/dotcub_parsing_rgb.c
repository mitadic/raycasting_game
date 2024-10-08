#include "../../includes/cub3d.h"

/* if bad, return and leave the value as initialized to -1, validate later */
static int  store_one_of_rgb(t_data *data, char *nptr, char where, int which)
{
    int i;

    if (ft_strlen(nptr) > 3)
        return (error("bad input for one of RGB values", KO));
    i = -1;
    while (++i < (int)ft_strlen(nptr))
    {
        if (!ft_isdigit(nptr[i]))
            return (error("non-digits found in R for RGB", KO));
    }
    if (where == 'C')
        data->map.ceiling[which] = atoi_cub3d_rgb(nptr);
    else if (where == 'F')
        data->map.floor[which] = atoi_cub3d_rgb(nptr);
    return (OK);
}

/* This shouldn't need string count of rgbs verification, we counted the commas */
static int extract_the_gb(t_data *data, char **rgbs, char where)
{
    char    *trimmed;
    int     i;
    int     qc_flag;

    i = 0;
    while (rgbs[++i])
    {
        trimmed = ft_strtrim(rgbs[i], WHITESPACES);
        if (!trimmed)
            return (error("malloc fail while extracting [G, B] of RGB", KO));
        qc_flag = store_one_of_rgb(data, trimmed, where, i);
        free(trimmed);
    }
    return (qc_flag);
}

static int  extract_the_r(t_data *data, char *left_of_comma, char where)
{
    char    *trimmed;
    char    **identifier_and_r;
    int     qc_flag;

    trimmed = ft_strtrim(left_of_comma, WHITESPACES);
    if (!trimmed)
        return (error("malloc fail while extracting rgb", KO));
    identifier_and_r = ft_split(trimmed, ' ');
    free(trimmed);
    if (!identifier_and_r)
        return (error("malloc fail while extracting rgb", KO));
    if (get_strings_count(identifier_and_r) != 2)
    {
        free_strarr(identifier_and_r);
        return (error("bad RGB values", KO));
    }
    trimmed = ft_strtrim(identifier_and_r[1], WHITESPACES);
    if (!trimmed)
    {
        free_strarr(identifier_and_r);
        return (error("malloc fail while extracting rgb", KO));
    }
    free_strarr(identifier_and_r);
    qc_flag = store_one_of_rgb(data, trimmed, where, 0);
    free(trimmed);
    return (qc_flag);
}

int extract_rgb(t_data *data, char *line, char where)
{
    char	**rgbs;

    if (get_char_count(line, ',') != 2)
        return (error("Expected 2x ',' separating the RGB", KO));
    rgbs = ft_split(line, ',');
    if (!rgbs)
        return (error("malloc fail while extracting rgb", KO));
    if (extract_the_r(data, rgbs[0], where) != OK || \
        extract_the_gb(data, rgbs, where) != OK)
    {
        free_strarr(rgbs);
        return (KO);
    }
    free_strarr(rgbs);
    return (OK);
}