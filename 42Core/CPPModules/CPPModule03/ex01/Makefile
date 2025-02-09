SRCS = ClapTrap.cpp ScavTrap.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
CC = c++
CXXFLAGS = -Werror -Wextra -Wall -std=c++98
NAME = ClapTrap
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
		$(CC) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re : fclean $(NAME)

.PHONY : all clean fclean re
