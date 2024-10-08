#include "../../includes/cub3d.h"

/* Set up player */
static void	init_player(t_data *data, int x, int y, char pl_orientation)
{
	data->pl_pos.x = x + 0.5;
	data->pl_pos.y = y + 0.5;
	if (pl_orientation == 'N')
		data->pl_pos.player_angle_degree = -90;
	else if (pl_orientation == 'E')
		data->pl_pos.player_angle_degree = 0;
	else if (pl_orientation == 'S')
		data->pl_pos.player_angle_degree = 90;
	else if (pl_orientation == 'W')
		data->pl_pos.player_angle_degree = -180;
}

/* Validates and stores player position. No need for pl_pos.<c> to be init'd */
int	locate_player(t_data *data)
{
	int y;
    int x;
	int	pl_pos_count;

    y = -1;
	pl_pos_count = 0;
    while (++y < data->map.max_y)
    {
        x = -1;
        while (++x < data->map.max_x)
		{
			if (ft_strchr(PLAYER_DIR, data->map.vals[x][y]))
			{
				init_player(data, x, y, data->map.vals[x][y]);
				pl_pos_count++;
			}
		}
    }
	if (pl_pos_count < 1)
		return (error(NOPL, KO));
	if (pl_pos_count > 1)
		return (error(TOOMANYPL, KO));
	return (OK);
}

/* Look for illegal symbols */
int	validate_map_symbols(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map.max_y)
	{
		x = -1;
		while (++x < data->map.max_x)
		{
			if (!ft_strchr(LEGAL_CHARS, data->map.vals[x][y]))
				return (error(ILLEGAL, KO));
		}
	}
	return (OK);
}

int	val_init_map(t_data *data)
{
	if (validate_map_symbols(data) != OK)
		return (KO);
	if (locate_player(data) != OK)
		return (KO);
	return (OK);
}
