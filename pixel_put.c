#include "puts.h"
#include "mlx.h"

void            pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->cam->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int             close1(t_img *vars)
{
	// (void)keycode;
	// printf("%d\n", keycode);
	// mlx_destroy_image(vars->mlx, vars->cam->addr);
    mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	exit(0);
}

int             close2(int keycode, t_img *vars)
{
	// printf("%d\n", keycode);
    if (keycode == 65307)
	{
		mlx_destroy_image(vars->mlx, vars->c_start->addr);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		exit(0);
	}
	return (0);
}

