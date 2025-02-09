SRCS = AMateria.cpp Cure.cpp Ice.cpp main.cpp Character.cpp MateriaSource.cpp
OBJS = $(SRCS:.cpp=.o)
CC = c++
CXXFLAGS = -Werror -Wextra -Wall -g3 -std=c++98
NAME = SpellCaster
RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
		$(CC) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
