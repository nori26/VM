# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/24 16:05:14 by nosuzuki          #+#    #+#              #
#    Updated: 2021/03/16 09:38:17 by nosuzuki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror 
AR		= ar
ARFLAGS	= scr
SRCDIR	= ./
SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
B_SRCS	= $(addprefix $(SRCDIR), $(B_NAME))
B_OBJS	= $(B_SRCS:.c=.o)
SRCNAME	= ft_bzero.c ft_memccpy.c ft_memcpy.c ft_memset.c ft_memmove.c\
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c\
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
		ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_isascii.c\
		ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_merge.c ft_extrlen.c free_all.c
B_NAME	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

all		: $(NAME)
.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME)	: $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^
bonus	: $(B_OBJS) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^
clean	:
	$(RM) $(OBJS) $(B_OBJS)
fclean	: clean
	$(RM) $(NAME)
re		: fclean all

.PHONY	: all clean fclean re bonus