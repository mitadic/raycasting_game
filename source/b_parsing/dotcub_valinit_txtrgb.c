/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotcub_valinit_txtrgb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 01:22:00 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/15 01:58:53 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	pack_rgb(int red, int green, int blue)
{
	return (((red << 16) | (green << 8) | blue) & 0xFFFFFF);
}

int	val_init_rgbs(t_data *data)
{
	int	i;

	if (!is_textures_and_rgbs_extr_complete(data))
		return (KO);
	i = -1;
	while (++i < 3)
	{
		if (data->map.ceiling[i] < 0 || data->map.floor[i] < 0 || \
			data->map.ceiling[i] > 255 || data->map.floor[i] > 255)
			return (error("bad RGB values", KO));
	}
	data->map.rgb_c = pack_rgb(data->map.ceiling[0], data->map.ceiling[1], \
								data->map.ceiling[2]);
	data->map.rgb_f = pack_rgb(data->map.floor[0], data->map.floor[1], \
								data->map.floor[2]);
	return (OK);
}

int	verify_texture_paths(t_data *data)
{
	int	i;
	int	fd[4];
	int	qc_flag;

	qc_flag = OK;
	fd[0] = open(data->map.no, O_RDONLY);
	fd[1] = open(data->map.ea, O_RDONLY);
	fd[2] = open(data->map.so, O_RDONLY);
	fd[3] = open(data->map.we, O_RDONLY);
	i = -1;
	while (++i < 4)
	{
		if (fd[i] < 0 || close(fd[i]) != OK)
			qc_flag = KO;
	}
	if (qc_flag == KO)
		put_err_msg(BADTXTPATH);
	return (qc_flag);
}

int	val_init_textures(t_data *data)
{
	int		i;
	t_img	*tx_img;

	data->mlx = mlx_init();
	if (!data->mlx)
		error_and_bail(data, "mlx_init fail", KO);
	data->txt[0].img = mlx_xpm_file_to_image(data->mlx, data->map.no, \
			&data->txt[0].size_x, &data->txt[0].size_y);
	data->txt[1].img = mlx_xpm_file_to_image(data->mlx, data->map.ea, \
			&data->txt[1].size_x, &data->txt[1].size_y);
	data->txt[2].img = mlx_xpm_file_to_image(data->mlx, data->map.so, \
			&data->txt[2].size_x, &data->txt[2].size_y);
	data->txt[3].img = mlx_xpm_file_to_image(data->mlx, data->map.we, \
			&data->txt[3].size_x, &data->txt[3].size_y);
	i = -1;
	while (++i < 4)
	{
		tx_img = data->txt[i].img;
		if (!tx_img || !tx_img->data)
			return (error(TEXTLOADFAIL, KO));
		if (tx_img->height != tx_img->width)
			return (error(NOTSQUARE, KO));
	}
	return (OK);
}

int	val_init_txtrgb(t_data *data)
{
	if (val_init_rgbs(data) != OK)
		return (KO);
	if (verify_texture_paths(data) != OK)
		return (KO);
	if (val_init_textures(data) != OK)
		return (KO);
	return (OK);
}
