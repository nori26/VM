NAME	= a.out
CC		= clang
CFLAGS	= -g -fsanitize=address -lm libmlx_Linux.a -lXext -lX11
AR		= ar
ARFLAGS	= scr
SRCDIR	= ./
SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
SRCNAME	= main.c pixel_put.c light.c vector_utils.c sphere.c

all		: $(NAME)
$(NAME)	: 
	$(CC) ${SRCNAME} $(CFLAGS)
san     :
	$(CC) $(CFLAGS) -g -fsanitize=address
bonus	: $(B_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^
clean	:
	$(RM) $(OBJS) $(B_OBJS)
fclean	: clean
	$(RM) $(NAME)
re		: fclean all

.PHONY	: all clean fclean re bonus