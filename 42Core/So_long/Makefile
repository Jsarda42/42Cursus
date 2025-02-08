# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 19:25:54 by juliensarda       #+#    #+#              #
#    Updated: 2024/01/10 11:07:55 by jsarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR),eod.c init_values.c check_rows_column.c map_parsing.c close_game.c free_mem.c check_map.c render_map.c main.c init_game.c utils.c init_map.c handle_input.c)
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
MLX_DIR = ./mlx

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

$(MLX_LIB):
	@make -C $(MLX_DIR)

.c.o:
	$(CC) $(CFLAGS) -g3 -c -o $@ $< $(INCLUDES)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re

