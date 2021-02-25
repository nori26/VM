NAME	= a.out
CC		= clang
CFLAGS	= -Wall -Werror -Wextra -lm libmlx_Linux.a -lXext -lX11 #-g -fsanitize=address
AR		= ar
ARFLAGS	= scr
SRCDIR	= ./
SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
SRCNAME	= main.c pixel_put.c light.c vector_utils.c sphere.c\
          get_next_line.c get_next_line_utils.c

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