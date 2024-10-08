#include "../../includes/cub3d.h"

/* if bad, return and leave the value as initialized to -1, validate later */
static void store_one_of_rgb(t_data *data, char *nptr, char where, int which)
{
    int i;

    if (ft_strlen(nptr) > 3)
        return (void_error("bad input for one of RGB values"));
    i = -1;
    while (++i < (int)ft_strlen(nptr))
    {
        if (!ft_isdigit(nptr[i]))
            return (void_error("non-digits found in R for RGB"));
    }
    if (where == 'C')
        data->map.ceiling[which] = atoi_cub3d_rgb(nptr);
    else if (where == 'F')
        data->map.floor[which] = atoi_cub3d_rgb(nptr);
}

/* This shouldn't need string count of rgbs verification, we counted the commas */
static void extract_the_gb(t_data *data, char **rgbs, char where)
{
    char    *trimmed;
    int i;

    i = 0;
    while (rgbs[++i])
    {
        trimmed = ft_strtrim(rgbs[i], WHITESPACES);
        if (!trimmed)
            return (void_error("malloc fail while extracting [G, B] of RGB"));
        store_one_of_rgb(data, trimmed, where, i);
        free(trimmed);
    }
}

static void extract_the_r(t_data *data, char *left_of_comma, char where)
{
    char    *trimmed;
    char    **identifier_and_r;

    trimmed = ft_strtrim(left_of_comma, WHITESPACES);
    if (!trimmed)
        return (void_error("malloc fail while extracting rgb"));
    identifier_and_r = ft_split(trimmed, ' ');
    free(trimmed);
    if (!identifier_and_r)
        return (void_error("malloc fail while extracting rgb"));
    if (get_strings_count(identifier_and_r) != 2)
    {
        free_strarr(identifier_and_r);
        return void_error("bad RGB values");
    }
    trimmed = ft_strtrim(identifier_and_r[1], WHITESPACES);
    if (!trimmed)
    {
        free_strarr(identifier_and_r);
        return (void_error("malloc fail while extracting rgb"));
    }
    store_one_of_rgb(data, trimmed, where, 0);
    free(trimmed);
    free_strarr(identifier_and_r);
}

void extract_rgb(t_data *data, char *line, char where)
{
    char	**rgbs;

    if (get_char_count(line, ',') != 2)
        return (void_error("Expected 2x ',' separating the RGB"));
    rgbs = ft_split(line, ',');
    if (!rgbs)
        return (void_error("malloc fail while extracting rgb"));
    extract_the_r(data, rgbs[0], where);
    extract_the_gb(data, rgbs, where);
    free_strarr(rgbs);
}