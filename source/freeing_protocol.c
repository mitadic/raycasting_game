#include "../includes/cub3d.h"

static void    free_map_vals(t_data *data)
{
    int y;

    y = -1;
    if (!data->map.vals)
        return ;
    while (++y < data->map.max_y)
        free(data->map.vals[y]);
    free(data->map.vals);
}

void    purge(t_data *data)
{
    free_map_vals(data);
    if (data->rays)
        free(data->rays);
}