NAME    = cub3d

INC     = -I include

LIBFTDIR	= inc/libft
LIBFT   	= $(LIBFTDIR)/libft.a# path to libft library
LIBMLXDIR 	= inc/minilibx-linux
LIBMLX  	= $(LIBMLXDIR)/libmlx_Linux.a# could be /usr/lib, depends on where you decided to put your mlx library
LFLAGS		= -L /bin/valgrind

CFLAGS  = -Wall -Werror -Wextra -O3 -g -fsanitize=address
UNAME   := $(shell uname)# get the OS name, this will help define behaviors for certain OS's

LFLAGS  	= -L$(LIBMLXDIR) -lmlx -L${LIBFTDIR} -lft $(LDFLAGS) -fsanitize=address# if you decided to install libmlx.a locally you don't need "-L$(LIBMLX) -lmlx" the school also has it locally as well...

SRC     = 	src/main.c				\
			src/validate_input.c	\

OBJ     = $(SRC:%.c=%.o)# convert source files to binary list

ifeq ($(UNAME), Darwin) # iMac / iOS
	CC = cc
	LFLAGS += -framework OpenGL -framework AppKit
else ifeq ($(UNAME), FreeBSD) # FreeBSD
	CC = clang
else #Linux and others...
	CC = cc
	LFLAGS += -lbsd -lXext -lX11 -lm
endif


all: $(NAME)

$(NAME): runlibft $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

runlibft:
	make -C $(LIBFTDIR) --no-print-directory

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJ		: $(OBJ)\n"