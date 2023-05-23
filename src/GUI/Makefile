##
## EPITECH PROJECT, 2023
## zappy
## File description:
## gui
##

TARGET			=			zappy_gui

CXX             =           g++
CFLAGS			=			-Wall -Wextra -Wpedantic -I./src/server
LDFLAGS			=			

SRC				=			src/Main.cpp						\
							src/server/ServerConnection.cpp

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
