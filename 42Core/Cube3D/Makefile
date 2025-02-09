NAME 			= cub3D
LIBFT_PATH 		= ./libft
MINILIBX_PATH   = ./mlx_linux
SRCS 			=	src/main.c \
					./src/close_game.c \
					./src/win_manager.c \
					./src/event_handlers.c \
					./src/draw_vertical_line.c \
					./src/distance.c \
					./src/utils.c \
					./src/utils2.c \
					./init/init_game.c \
					./init/init_map.c \
					./init/init_texture.c \
					./init/init_window.c \
					./parsing/parse_map.c \
					./parsing/parse_map_utils.c \
					./parsing/parsing_utils.c \
					./parsing/parse_cardinals.c \
					./parsing/parse_colors.c \
					./parsing/parse_colors_utils.c \
					./parsing/parse_identifier.c \
					./parsing/parse_map_grid.c \
					./parsing/player_init.c \
					./utils/free.c \
					./utils/ft_errors.c \

OBJS			= ${SRCS:.c=.o}
INCLUDE 		= cube3d.h
LIBFT 			= libft
CC				= cc -g3 -Wall -Wextra -Werror -I ./includes -I ./mlx_linux
RM				= rm -f
LIBFLAGS 		= -I ./libft -L ./libft -lft
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_LIB = $(MINILIBX_PATH)/libmlx.a
	MLX_FLAGS = -I ./mlx_linux -L ./mlx_linux -lmlx -lX11 -lXext -lm
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_LIB = $(MINILIBX_PATH)/libmlx.a
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

all:			${NAME}
$(NAME):		${OBJS} libft.a libmlx.a
				@$(CC) $(OBJS) $(LIBFLAGS) $(MLX_FLAGS) -o $@
%.o: %.c
				$(CC) -c $< -o $@
libft.a:
		$(MAKE) -C $(LIBFT_PATH)
		cp $(LIBFT_PATH)/libft.a .
libmlx.a:
		$(MAKE) -C $(MINILIBX_PATH)
		cp $(MINILIBX_PATH)/libmlx.a .
clean:			libft_clean minilibx_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
				@${RM} ${NAME} libft.a libmlx.a
re:				fclean all

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft.a

minilibx_clean:
	make -C $(MINILIBX_PATH) clean
	$(RM) libmlx.a

norm:
	find . -path ./mlx_linux -prune -o -name 'Makefile' -prune -o -name '*.c' -print -o -name '*.h' -print | xargs norminette


.PHONY: all fclean clean re
