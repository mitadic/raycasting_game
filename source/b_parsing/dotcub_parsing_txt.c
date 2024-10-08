#include "../../includes/cub3d.h"

/* deep-copied texture path is stored */
void    store_one_txt(t_data *data, char *txt_str, char where)
{
    if (where == 'N')
        data->map.no = txt_str;
    else if (where == 'E')
        data->map.ea = txt_str;
    else if (where == 'S')
        data->map.so = txt_str;
    else if (where == 'W')
        data->map.we = txt_str;
}

/* ft_strtrim deep-copies the cleaned up texture path, as intended, no free */
void extract_texture(t_data *data, char *line, char where)
{
    char	**identifier_and_txt;
    char    *txt_str;

    identifier_and_txt = ft_split(line, ' ');
    if (!identifier_and_txt)
        return (void_error("malloc fail extracting texture"));
    if (get_strings_count(identifier_and_txt) != 2)
    {
        free_strarr(identifier_and_txt);
        return (void_error("illegal texture specification"));
    }
    txt_str = ft_strtrim(identifier_and_txt[1], WHITESPACES);
    if (!txt_str)
    {
        free_strarr(identifier_and_txt);
        return (void_error("malloc fail extracting texture"));
    }
    store_one_txt(data, txt_str, where);
    free_strarr(identifier_and_txt);
}