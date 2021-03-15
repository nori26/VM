#include "puts.h"

void            pixel_put(t_pic *data, int x, int y, int color)
{
    char    *dst;

    dst = data->cam->adr + (y * data->width_bytes + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int             close1(t_pic *img)
{
	close_img(img);
	exit(0);
}

int             close2(int keycode, t_pic *img)
{
	// printf("%d\n", keycode);
	// printf("%d\n", keycode);
    if (keycode == ESC)
	{
		close_img(img);
		exit(0);
	}
	if (keycode == RIGHT)
		img->cam = img->cam->next;
	if (keycode == LEFT)
		img->cam = img->cam->prev;;
	return (0);
}
