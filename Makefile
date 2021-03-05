NAME    = a.out
CC      = clang
CFLAGS  =  -lm libmlx_Linux.a -lXext -lX11 -Wall -Werror -Wextra
AR      = ar
ARFLAGS = scr
SRCDIR  = ./
SRCS    = $(addprefix $(SRCDIR), $(SRCNAME))
OBJS    = $(SRCS:.c=.o)
SRCNAME = main.c pixel_put.c light.c vector_utils.c sphere.c get_next_line.c world_init.c read_rt.c object_init.c

all     : $(NAME)

$(NAME) : 
	$(MAKE) -C ./libft
	cp ./libft/libft.a .
	$(CC) ${SRCNAME} libft.a $(CFLAGS)

san	    :
	$(MAKE) -C ./libft
	cp ./libft/libft.a .
	$(CC) ${SRCNAME} libft.a $(CFLAGS) -g -fsanitize=address

bonus   : $(B_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^

clean   :
	$(RM) $(OBJS) $(B_OBJS)

fclean  : clean
	$(RM) $(NAME)

re      : fclean all

.PHONY  : all clean fclean re bonus