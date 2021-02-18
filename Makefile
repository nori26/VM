NAME	= a.out
CC		= clang
CFLAGS	= pixel_put.c main.c vector_utils.c -lm libmlx_Linux.a -lXext -lX11
AR		= ar
ARFLAGS	= scr
SRCDIR	= ./
SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
SRCNAME	= pixel_put.c main.c

all		: $(NAME)
$(NAME)	: 
	$(CC) $(CFLAGS)
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