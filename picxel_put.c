#include "puts.h"
#include "mlx.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             close1(int keycode, t_data *vars)
{
	printf("%d\n", keycode);
	mlx_loop_end(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	exit(0);
}

int             close2(int keycode, t_data *vars)
{
	printf("%d\n", keycode);
    if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		exit(0);
	}
	return (0);
}