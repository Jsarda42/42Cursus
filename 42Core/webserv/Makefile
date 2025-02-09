MAKEFLAGS += --jobs
NAME = webserv
SRCS = main.cpp \
	  ./server/HttpServer.cpp \
	  ./parsing/ParsedData.cpp \
	  ./parsing/ParseClientUtils.cpp \
	  ./parsing/ParseStatusMessage.cpp  \
	  ./utils/Lib.cpp \
	  ./server/Server.cpp \
	  ./parsing/ParseConfig.cpp \
	  ./server/Folder.cpp \
	  ./parsing/ParseType.cpp \
	  ./server/Php.cpp \
	  ./server/ServerLocation.cpp \
	  ./server/HttpServerSender.cpp

OBJS = $(SRCS:.cpp=.o)
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -I./config/ -I./server/ -I./parsing/ -I./utils/

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
