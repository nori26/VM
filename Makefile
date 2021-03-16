NAME    = miniRT
CC      = gcc
CFLAGS  =  -lm libmlx_Linux.a -lXext -lX11 -Wall -Werror -Wextra
AR      = ar
ARFLAGS = scr
SRCDIR  = ./
SRCS    = $(addprefix $(SRCDIR), $(SRCNAME))
OBJS    = $(SRCS:.c=.o)
SRCNAME = main.c pixel_put.c light.c vector_utils.c object.c\
        object_utils.c get_next_line.c world_init.c read_rt.c\
		object_init.c list_new.c list_add.c cylinder.c bmp.c\
		free.c vector_utils2.c read_rt_utils.c read_rt_utils2.c\
		obj_ray_to_raystart.c obj_ret_to_cam.c obj_to_cam.c\
		obj_update_node.c camera.c shadow.c raytrace.c

all     : $(NAME)

$(NAME) :
	$(MAKE) -C ./libft
	cp ./libft/libft.a .
	$(CC) ${SRCNAME} libft.a $(CFLAGS)

san	    :
	$(MAKE) -C ./libft
	cp ./libft/libft.a .
	$(CC) ${SRCNAME} libft.a $(CFLAGS) -g -fsanitize=address

clean   :
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(B_OBJS)

fclean  : clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re      : fclean all

.PHONY  : all clean fclean re bonus