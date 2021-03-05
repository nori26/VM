#include "mlx.h"
#include <stdlib.h>
typedef struct	s_test
{
	void *mlx;
	void *win;
}				t_test;

int             closet(t_test *vars)
{
	// (void)vars;
	// printf("%d\n", keycode);
	// mlx_loop_end(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	exit(0);
}

int main()
{
	t_test t;
	int		x;
	int		y;

	x = 1;
	y = 1;
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, x, y, "aaa");
	mlx_hook(t.win, 33, 1 << 17, closet, &t);
	mlx_loop(t.mlx);
}