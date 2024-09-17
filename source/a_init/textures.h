#ifndef TEXTURES_H
# define TEXTURES_H

///////////////////////////////////
// FAKES

# define KO 1
# define OK 0
# define TILE_SIZE 64
# define SCREEN_W 640
# define SCREEN_H 480

/*
cc -g init_textures.c -L../../minilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
*/

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../minilibx-linux/mlx.h"
# include "../../minilibx-linux/mlx_int.h"

///////////////////////////////////
// REAL

typedef struct  s_text
{
    int pixels[TILE_SIZE][TILE_SIZE];
}   t_text;

///////////////////////////////////
// FAKES

typedef struct s_img_buff
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_buff;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img_buff	img_buff;
    t_text      texture[4];
}	t_data;

#endif