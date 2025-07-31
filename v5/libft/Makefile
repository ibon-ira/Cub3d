# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 11:59:04 by iksaiz-m          #+#    #+#              #
#    Updated: 2024/04/14 19:27:12 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_toupper.c ft_memcmp.c ft_bzero.c ft_memset.c \
	ft_tolower.c ft_memchr.c ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_strnstr.c \
	ft_strncmp.c ft_memcpy.c ft_memmove.c ft_strlcat.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_functions.c ft_printf.c get_next_line_bonus.c \
	get_next_line_utils_bonus.c
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = rcs

OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@ $(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS) 
	@ $(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus