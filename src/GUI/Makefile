##
## EPITECH PROJECT, 2023
## zappy
## File description:
## gui
##

TARGET			=			zappy_gui

CXX             =           g++
CFLAGS			=			-Wall -Wextra -Wpedantic -I./src/server -I./src/window
LDFLAGS			=			-lsfml-graphics -lsfml-window -lsfml-system

SRC				=			src/Main.cpp						\
							src/server/ServerConnection.cpp		\
							src/window/Window.cpp

OBJ				=			$(SRC:.cpp=.o)

RM				?=			rm -f

all: $(TARGET)

$(TARGET):	$(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(TARGET)

re: fclean all
