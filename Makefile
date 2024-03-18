# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 19:35:23 by diosanto          #+#    #+#              #
#    Updated: 2024/03/18 00:52:27 by micarrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

INC     = -I include

LIBFTDIR	= inc/libft
LIBFT   	= $(LIBFTDIR)/libft.a# path to libft library
LIBMLXDIR 	= inc/minilibx-linux
LIBMLX  	= $(LIBMLXDIR)/libmlx_Linux.a# could be /usr/lib, depends on where you decided to put your mlx library
LFLAGS		= -L /bin/valgrind
CC			= cc

CFLAGS  = -Wall -Werror -Wextra -pthread -g -O3 $(LDFLAGS) #-fsanitize=address
UNAME   := $(shell uname)

SRC     = 	src/main.c			 	\
			src/validate_input.c	\
			src/validate_input2.c	\
			src/validate_input3.c	\
			src/process_imgs.c		\
			src/key_press.c			\
			src/player_mov.c		\
			src/parser.c			\
			src/raycasting.c		\
			src/raycasting_utils.c	\
			src/collision.c			\
			src/exit_functions.c	\
			src/mouse.c				\
			src/raycaster_draw.c

OBJ     = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -L$(LIBMLXDIR) -lft -Linc/minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

# $(OBJ): $(SRC)
# 	$(CC) -c $(SRC) $(CFLAGS)

runlibft:
	make -C $(LIBFTDIR) 

clean:
	$(MAKE) clean -C inc/libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C inc/libft
	rm -f $(NAME)

re: fclean all