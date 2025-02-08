# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 11:32:07 by jsarda            #+#    #+#              #
#    Updated: 2024/02/05 14:46:28 by jsarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
NAMESV = server
NAMEBONUS = client_bonus
NAMESVBONUS = server_bonus

SRCS =  ./src/client.c
SRCSSV = ./src/server.c
SRCSBONUS = ./src/client_bonus.c
SRCSSVBONUS = ./src/server_bonus.c

OBJS = ${SRCS:.c=.o}
OBJSSV = ${SRCSSV:.c=.o}
OBJSBONUS = ${SRCSBONUS:.c=.o}
OBJSSVBONUS = ${SRCSSVBONUS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: ${NAME} ${NAMESV}
${NAME} : ${OBJS}
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME}
${NAMESV}: ${OBJSSV}
	@${CC} ${CFLAGS} ${OBJSSV} ./libft/libft.a -o ${NAMESV}

bonus: ${NAMEBONUS} ${NAMESVBONUS}
${NAMEBONUS} : ${OBJSBONUS}
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} ${OBJSBONUS} ./libft/libft.a -o ${NAMEBONUS}
${NAMESVBONUS} : ${OBJSSVBONUS}
	@${CC} ${CFLAGS} ${OBJSSVBONUS} ./libft/libft.a -o ${NAMESVBONUS}

clean:
	@${MAKE} -C ./libft fclean
	@${RM} ${OBJS}
	@${RM} ${OBJSSV}
	@${RM} ${OBJSBONUS}
	@${RM} ${OBJSSVBONUS}

fclean: clean
	@${RM} ${NAME} ${NAMESV}
	@${RM} ${NAME} ${NAMESV}
	@${RM} ${NAMEBONUS} ${NAMESVBONUS}

re: fclean all

.PHONY: all bonus clean fclean re
