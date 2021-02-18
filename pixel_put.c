#include "puts.h"
#include "mlx.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int             close1(int keycode, t_data *vars)
{
	// printf("%d\n", keycode);
	// mlx_loop_end(vars->mlx);
    // mlx_destroy_window(vars->mlx, vars->win);
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

double	inner(t_vec v1, t_vec v2)
{
	double ret;

	ret = v1.x * v2.x + v1.y + v2.y * v1.z * v2.z;
	return (ret);
}

t_vec	outer(t_vec v1, t_vec v2)
{
	t_vec ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}
