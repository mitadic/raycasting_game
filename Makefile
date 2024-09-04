CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
NAME		= cub3d
MLX			= libmlx_Linux.a
LIBFT		= libft.a
SRCD		= ./source/
INCLUDESD	= ./includes/
LIBFTD		= ./libft/
LIBMLXD 	= ./minilibx-linux/

SRC = 		main.c \
			init.c \
			map_parsing_control.c \
			map_parsing_flood_fill.c \
			map_parsing_flood_sim.c \
			failure_management.c \
			freeing_protocol.c

HFILES =	cub3d.h \
			errors.h

all: $(LIBFT) $(LIBMLXD) $(NAME)

$(LIBMLXD):
	@if [ ! -d $(LIBMLXD) ]; then \
		echo "Cloning minilibx-linux..."; \
		git clone git@github.com:42Paris/minilibx-linux.git $(LIBMLXD); \
	fi

$(NAME): $(addprefix $(SRCD),$(SRC)) $(addprefix $(INCLUDESD),$(HFILES)) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(addprefix $(SRCD),$(SRC)) -I$(INCLUDESD) -L$(LIBFTD) -lft -o $(NAME)

# -L$(LIBMLXD) -lmlx_Linux -L/usr/lib -Iminilibx-linux \
# -lXext -lX11 -lm -lz -o $(NAME)

$(MLX):
	make -C $(LIBMLXD) all

$(LIBFT):
	git submodule init
	git submodule update
	make -C $(LIBFTD) all

clean:
	make -C $(LIBFTD) clean
	# libminilibx Makefile (and its 'configure') do not
	# handle *.o files, it's essentially fclean only 
	rm -f *.o

fclean:	clean
	rm -f $(NAME)
	make -C $(LIBFTD) fclean
	# in libminilibx Makefile, 'clean' is essentially fclean
	make -C $(LIBMLXD) clean

re:	fclean all

.PHONY: all re clean fclean