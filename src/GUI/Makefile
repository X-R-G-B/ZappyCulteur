##
## EPITECH PROJECT, 2023
## zappy
## File description:
## gui
##

TARGET			=			zappy_gui

CXX             =           g++
CFLAGS			=			-Wall -Wextra -Wpedantic
LDFLAGS			=			

SRC				=			src/Main.cpp						\
							src/server/ServerConnection.cpp		\

SRC_INCLUDE		=			src/server/ServerConnection.hpp

OBJ				=			$(SRC:.cpp=.o)

RM				?=			rm -f

all: $(TARGET)

$(TARGET):	$(OBJ)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(TARGET)

re: fclean all
