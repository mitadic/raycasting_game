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
			$(MATH)raycasting3.c \
			$(MLXING)go_mlxing.c \
			$(MLXING)key_handling.c \
			$(MLXING)player_movements.c \
			$(MLXING)player_movements2.c \
			$(TEXTURES)draw_columns.c

NC		:=	\033[0m
GOLD	:=	\033[0;33m
CYAN	:=	\033[0;36m

ifdef BONUS_MODE
	SRC += $(MLXING)bonus_minimap.c
	SRC += $(MLXING)bonus_minimap2.c
	SRC += $(MLXING)bonus_mouse_rotation.c
	NAME = cub3d_bonus
endif

HFILES =	cub3d.h \
			errors.h \
			color_codes.h

# needed to move LIBFT and MLX dependences from NAME: to all: to prevent relinking
# due to @if. One other side-effect of @if: no "Nothing to be done" printout.
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(addprefix $(SRCD),$(SRC)) $(addprefix $(INCLUDESD),$(HFILES))
	$(CC) $(CFLAGS) $(addprefix $(SRCD),$(SRC)) -I$(INCLUDESD) -L$(LIBFTD) -lft -o $(NAME) -lm \
	-L$(LIBMLXD) -lmlx -L/usr/lib -Iminilibx-linux \
	-lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	@if [ ! -d ./libft ]; then \
		echo -e "Cloning $(CYAN)libft$(NC)..."; \
		git clone git@github.com:MilosTadic01/my_library.git libft; \
		make -sC $(LIBFTD) all; \
		echo -e "-----\n$(CYAN)Libft$(NC) cloning done!\n-----"; \
	fi
	@if [ ! -f ./libft/libft.a ]; then \
		echo -e "Making $(CYAN)libft$(NC)..."; \
		make -sC $(LIBFTD) all; \
		echo -e "-----\n$(CYAN)Libft$(NC) making done!\n-----"; \
	fi

$(MLX):
	@if [ ! -d ./minilibx-linux ]; then \
		echo -e "Cloning $(CYAN)minilibx-linux$(NC)..."; \
		git clone git@github.com:MilosTadic01/minilibx-linux.git; \
		echo -e "-----\n$(CYAN)Minilibx$(NC) done!\n-----"; \
	fi
	@if [ ! -f ./minilibx-linux/libmlx_Linux.a ]; then \
		echo -e "Making $(CYAN)Minilibx$(NC)..."; \
		make -sC $(LIBMLXD) all; \
		echo -e "-----\n$(CYAN)Minilibx$(NC) making done!\n-----"; \
	fi

# We're not sure why ar fails for MLX in recursive MAKE call, better to depend
bonus: $(LIBFT) $(MLX) 
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
	@if [ -f cub3d_bonus ]; then \
		rm cub3d_bonus; \
	fi

re:	fclean all

.PHONY: all re clean fclean bonus