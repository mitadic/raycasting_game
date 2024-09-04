#include "../includes/cub3d.h"

static void    free_map_vals(t_data *data)
{
    int x;

    x = -1;
    if (!data->map.vals)
        return ;
    while (++x < data->map.max_x)
        free(data->map.vals[x]);
    free(data->map.vals);
}

void    purge(t_data *data)
{
    free_map_vals(data);
    if (data->rays)
        free(data->rays);
}