CC = c++
NAME = MutantStack
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
RM = rm -rf

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

.PHONY: clean fclean all re