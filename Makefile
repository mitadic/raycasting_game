CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
NAME		= cub3d
LIBFT		= libft.a
MLX			= libmlx_Linux.a
SRCD		= ./source/
INIT		= a_init/
PARSING		= b_parsing/
INCLUDESD	= ./includes/
LIBFTD		= ./libft/
LIBMLXD 	= ./minilibx-linux/

SRC = 		main.c \
			$(INIT)init.c \
			$(PARSING)map_parsing_control.c \
			$(PARSING)map_parsing_flood_fill.c \
			$(PARSING)map_parsing_flood_sim.c \
			$(PARSING)failure_management.c \
			$(PARSING)freeing_protocol.c

HFILES =	cub3d.h \
			errors.h

all: init_submodules $(LIBFT) $(LIBMLXD) $(NAME)

# delete this once submodule minilibx thoroughly tested:
# $(LIBMLXD):
# 	@if [ ! -d $(LIBMLXD) ]; then \
# 		echo "Cloning minilibx-linux..."; \
# 		git clone git@github.com:42Paris/minilibx-linux.git $(LIBMLXD); \
# 	fi

$(NAME): $(addprefix $(SRCD),$(SRC)) $(addprefix $(INCLUDESD),$(HFILES)) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(addprefix $(SRCD),$(SRC)) -I$(INCLUDESD) -L$(LIBFTD) -lft -o $(NAME)
# -L$(LIBMLXD) -lmlx_Linux -L/usr/lib -Iminilibx-linux \
# -lXext -lX11 -lm -lz -o $(NAME)

init_submodules:
	git submodule init
	git submodule update

$(LIBFT):
	make -C $(LIBFTD) all

$(MLX):
	make -C $(LIBMLXD) all

# libminilibx Makefile (and its 'configure') do not
# handle *.o files, it's essentially fclean only 
clean:
	make -C $(LIBFTD) clean
	rm -f *.o

# in libminilibx Makefile, 'clean' is essentially fclean
fclean:	clean
	rm -f $(NAME)
	make -C $(LIBFTD) fclean
	make -C $(LIBMLXD) clean

re:	fclean all

.PHONY: all re clean fclean init_submodules