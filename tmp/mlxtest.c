#include "mlx.h"
#include "puts.h"

int     main(void)
{
	t_pic  img;

	img.w = 1920;
	img.h = 975;
    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.w, img.h, "Hello world!");
	// img.img = mlx_new_image(img.mlx, img.w, img.h);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	int x = 0;
	int y = 0;
	mlx_get_screen_size(img.mlx, &x, &y);
	printf("%d\n%d\n", x, y);
	mlx_hook(img.win, 2, 1L << 0, close2, &img);
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
