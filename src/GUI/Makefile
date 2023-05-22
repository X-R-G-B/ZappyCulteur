##
## EPITECH PROJECT, 2023
## zappy
## File description:
## gui
##

TARGET			=			zappy_gui

CFLAGS			=			-Wall -Wextra -Wpedantic
LDFLAGS			=			

SRC				=			src/Main.cpp

OBJ				=			$(SRC:.cpp=.o)

RM				?=			rm -f

all: $(TARGET)

$(TARGET):	$(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(TARGET)

re: fclean all
