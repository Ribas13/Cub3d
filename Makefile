# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 19:35:23 by diosanto          #+#    #+#              #
#    Updated: 2024/03/24 15:07:48 by diosanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D

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
			src/parser2.c			\
			src/parser3.c			\
			src/parser4.c			\
			src/raycasting.c		\
			src/raycasting_utils.c	\
			src/exit_functions.c	\
			src/mouse.c				\
			src/update_textures.c	\
			src/init_player_dir.c	\
			src/collisions.c

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