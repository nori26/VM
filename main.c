#include "mlx.h"
#include "puts.h"



int     main(void)
{
	t_data  img;
    int     img_width;
    int     img_height;

    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 800, 800, "Hello world!");
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	// img.img = mlx_new_image(img.mlx, 800, 800);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                         &img.endian);
	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	// mlx_hook(img.win, 2, 1L<<0, close2, &img);
	// img.img = mlx_xpm_file_to_image(img.mlx, "./test.xpm", &img_width, &img_height);
    // mlx_loop_hook(img.mlx, render_next_frame, &img);
    mlx_loop(img.mlx);
}
