
// exiters.c
int		close_esc(int keycode, void *param);
int		close_x(t_vars *vars);

void	go_mlxing(t_vars *vars, t_data *img)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		purge(vars);
	vars->win = mlx_new_window(vars->mlx, IMG_WIDTH, IMG_HEIGHT, "FdF");
	if (!vars->win)
		purge(vars);
	img->img = mlx_new_image(vars->mlx, IMG_WIDTH, IMG_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	points_2d(vars);
	edges(vars, img);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	mlx_hook(vars->win, 2, 1L << 0, close_esc, (void *)vars);
	mlx_hook(vars->win, 17, 1L << 3, close_x, (void *)vars);
	mlx_loop(vars->mlx);
}

int	mlx_hook(t_win_list *win, int x_event, int x_mask, 
		 int (*funct)(),void *param)
{
  win->hooks[x_event].hook = funct;
  win->hooks[x_event].param = param;
  win->hooks[x_event].mask = x_mask;
}