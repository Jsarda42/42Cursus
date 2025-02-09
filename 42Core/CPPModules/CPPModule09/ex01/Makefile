SRCS = main.cpp RPN.cpp
CXXFLAGS = -Werror -Wextra -Wall -pedantic -std=c++98
OBJS = $(SRCS:.cpp=.o)
NAME = RPN
RM = rm -rf
CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.phony: re all clean fclean