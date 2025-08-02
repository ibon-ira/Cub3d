# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/15 20:34:57 by iksaiz-m          #+#    #+#              #
#    Updated: 2025/07/31 19:56:30 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			 = cc
LIBFT_DIR    = libft/
LIBFT        = $(LIBFT_DIR)libft.a
MINILIBX_DIR = minilibx-linux/
MINILIBX     = $(MINILIBX_DIR)libmlx.a
HEADERS      = -I $(LIBFT_DIR)
CFLAGS       = -Wall -Wextra -Werror -O3 -g -g3

NAME         = cub3d
RM           = rm -rf
SRC = stuff.c  utils.c utils2.c utils3.c utils4.c utils5.c utils6.c utils7.c freemem.c parselineutils.c asignatributes.c raycasting.c drawing.c

OBJS = $(SRC:.c=.o)

all: $(MINILIBX) $(LIBFT) $(NAME)
$(NAME): $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(MINILIBX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lm -lX11 -lXext

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
