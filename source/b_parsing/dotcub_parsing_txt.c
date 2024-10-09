#include "../../includes/cub3d.h"

/* strtrimmed (deep-copied) texture path gets stored, or freed if conflicts */
static int	store_one_txt(t_data *data, char *txt_str, char where)
{
	char	**struct_ptr;

	struct_ptr = NULL;
	if (where == 'N')
		struct_ptr = &(data->map.no);
	else if (where == 'E')
		struct_ptr = &(data->map.ea);
	else if (where == 'S')
		struct_ptr = &(data->map.so);
	else if (where == 'W')
		struct_ptr = &(data->map.we);
	if (*struct_ptr != NULL)
	{
		free(txt_str);
		return (error(ALREADYSTORED, KO));
	}
	*struct_ptr = txt_str;
	return (OK);
}

/* ft_strtrim deep-copies the cleaned up texture path, as intended, no free */
int	extract_texture(t_data *data, char *line, char where)
{
	char	**identifier_and_txt;
	char    *txt_str;
	int		qc_flag;

	identifier_and_txt = ft_split(line, ' ');
	if (!identifier_and_txt)
		return (error("malloc fail extracting texture", KO));
	if (get_strings_count(identifier_and_txt) != 2)
	{
		free_strarr(identifier_and_txt);
		return (error("illegal texture specification", KO));
	}
	txt_str = ft_strtrim(identifier_and_txt[1], WHITESPACES);
	if (!txt_str)
	{
		free_strarr(identifier_and_txt);
		return (error("malloc fail extracting texture", KO));
	}
	free_strarr(identifier_and_txt);
	qc_flag = store_one_txt(data, txt_str, where);
	return (qc_flag);
}