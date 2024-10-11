CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= cub3d
LIBFT		= libft.a
MLX			= libmlx_Linux.a
SRCD		= ./source/
INIT		= a_init/
PARSING		= b_parsing/
MATH		= c_math/
MLXING		= d_mlxing/
TEXTURES	= e_textures/
META		= z_meta/
INCLUDESD	= ./includes/
LIBFTD		= ./libft/
LIBMLXD 	= ./minilibx-linux/
BONUS_MODE  = 0
SRC = 		main.c \
			$(INIT)init.c \
			$(INIT)set_max_vector_values.c \
			$(PARSING)dotcub_parsing_control.c \
			$(PARSING)dotcub_parsing_extraction.c \
			$(PARSING)dotcub_parsing_getsingle_txtrgb.c \
			$(PARSING)dotcub_parsing_rgb.c \
			$(PARSING)dotcub_parsing_txt.c \
			$(PARSING)dotcub_valinit_map.c \
			$(PARSING)dotcub_valinit_txtrgb.c \
			$(PARSING)map_parsing_flood_fill.c \
			$(PARSING)map_parsing_flood_sim.c \
			$(PARSING)utils.c \
			$(META)failure_management.c \
			$(META)freeing_protocol.c \
			$(MATH)helper_functions.c \
			$(MATH)raycasting.c \
			$(MATH)raycasting2.c \
			$(MLXING)go_mlxing.c \
			$(MLXING)player_movements.c \
			$(TEXTURES)draw_columns.c


HFILES =	cub3d.h \
			errors.h \
			color_codes.h

ifeq ($(BONUS_MODE), 1)
	SRC += $(MLXING)bonus_minimap.c
endif

all: init_submodules $(LIBFT) $(LIBMLXD) $(NAME)

# delete this once submodule minilibx thoroughly tested:
$(LIBMLXD):
	@if [ ! -d $(LIBMLXD) ]; then \
		echo "Cloning minilibx-linux..."; \
		git clone git@github.com:42Paris/minilibx-linux.git $(LIBMLXD); \
	fi

$(NAME): $(addprefix $(SRCD),$(SRC)) $(addprefix $(INCLUDESD),$(HFILES)) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(addprefix $(SRCD),$(SRC)) -I$(INCLUDESD) -L$(LIBFTD) -lft -o $(NAME) -lm \
	-L$(LIBMLXD) -lmlx -L/usr/lib -Iminilibx-linux \
	-lXext -lX11 -lm -lz -o $(NAME)

init_submodules:
# git submodule init
# git submodule update

$(LIBFT):
	make -C $(LIBFTD) all

$(MLX):
	make -C $(LIBMLXD) all

bonus:$(MLX)  # Ensure MinilibX is built when running make bonus
	@$(MAKE) BONUS_MODE=1 CFLAGS="-DBONUS=1" all

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

.PHONY: all re clean fclean bonus init_submodules