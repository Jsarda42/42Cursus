SRCS = Account.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CC = c++
RM = rm -f

NAME = Account

all: $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
		$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean: clean
		$(RM) $(NAME)
re: fclean $(NAME)

.PHONY: all clean fclean re
