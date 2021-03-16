NAME    = miniRT
CC      = gcc
CFLAGS  =  -Wall -Werror -Wextra -lm -lXext -lX11
AR      = ar
ARFLAGS = scr
SRCDIR  = ./
MLX		= minilibx-linux
SRCS    = $(addprefix $(SRCDIR), $(SRCNAME))
OBJS    = $(SRCS:.c=.o)
SRCNAME = main.c pixel_put.c light.c vector_utils.c object.c\
        object_utils.c get_next_line.c world_init.c read_rt.c\
		object_init.c list_new.c list_add.c cylinder.c bmp.c\
		free.c vector_utils2.c read_rt_utils.c read_rt_utils2.c\
		obj_ray_to_raystart.c obj_ret_to_cam.c obj_to_cam.c\
		obj_update_node.c camera.c shadow.c raytrace.c

all     : $(NAME)

$(MLX) :
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX)
$(NAME) : $(MLX) ${OBJS}
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx-linux
	cp ./minilibx-linux/libmlx_Linux.a .
	cp ./libft/libft.a .
	$(CC) ${OBJS} libmlx_Linux.a libft.a $(CFLAGS) -o ${NAME}

san	    : ${OBJS}
	git clone https://github.com/42Paris/minilibx-linux.git
	$(MAKE) -C ./libft
	$(MAKE) -C ${MLX}
	cp ./minilibx-linux/libmlx_Linux.a .
	cp ./libft/libft.a .
	$(CC) -g -fsanitize=address ${OBJS} libmlx_Linux.a libft.a $(CFLAGS) -o ${NAME}

clean   : ${MLX}
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ${MLX}
	$(RM) $(OBJS) $(B_OBJS)

fclean  : clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) libft.a libmlx_Linux.a

re      : fclean all

.PHONY  : all clean fclean re bonus