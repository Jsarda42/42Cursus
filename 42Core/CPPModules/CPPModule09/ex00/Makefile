CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g3
SRCS = 	main.cpp\
		BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = btc

all: $(NAME)

$(NAME):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
