SRC		=	src/main.cpp					\
			src/Game.cpp					\
			src/ChessMan.cpp				\
			src/Referee.cpp					\
			src/Informations.cpp


OBJ		=	$(SRC:.cpp=.o)

RM		=	rm -f
CC		=	g++

CXXFLAGS	=	-Wall -Wextra -I./include


LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

NAME		=	chess

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all