# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 19:35:23 by diosanto          #+#    #+#              #
#    Updated: 2024/02/13 16:26:41 by diosanto         ###   ########.fr        #
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

CFLAGS  = -Wall -Werror -Wextra -O3 -g $(LDFLAGS) #-fsanitize=address
UNAME   := $(shell uname)

SRC     = 	src/main.c			 	\
			src/validate_input.c	\
			src/process_imgs.c

OBJ     = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	$(CC) $(OBJ) -L$(LIBFTDIR) -L$(LIBMLXDIR) -lft -Linc/minilibx-linux -lmlx -lXext -lX11 -o $(NAME)

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