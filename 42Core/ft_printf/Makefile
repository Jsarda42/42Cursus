SRCS = ft_eval_format.c ft_print_char.c ft_print_nbr_unsigned.c ft_print_nbr.c ft_print_ptr_hexa.c ft_print_ptr.c ft_print_str.c ft_printf.c
OBJS = $(SRCS:.c=.o)
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
