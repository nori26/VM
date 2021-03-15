#include "puts.h"

void            pixel_put(t_pic *data, int x, int y, int color)
{
    char    *dst;

    dst = data->cam->adr + (y * data->width_bytes + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int             close1(t_pic *vars)
{
	// (void)keycode;
	// printf("%d\n", keycode);
	// mlx_destroy_image(vars->mlx, vars->cam->addr);
    mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

int             close2(int keycode, t_pic *img)
{
	// printf("%d\n", keycode);
	// printf("%d\n", keycode);
    if (keycode == ESC)
	{
		mlx_destroy_image(img->mlx, img->cam->img);
		mlx_destroy_window(img->mlx, img->win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		exit(0);
	}
	if (keycode == RIGHT)
		img->cam = img->cam->next;
	if (keycode == LEFT)
		img->cam = img->cam->prev;;
	return (0);
}
