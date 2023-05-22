##
## EPITECH PROJECT, 2023
## zappy
## File description:
## server
##

TARGET			=			zappy_server

CFLAGS			=			-Wall -Wextra -Wpedantic
LDFLAGS			=			

SRC				=			src/main.c

OBJ				=			$(SRC:.c=.o)

RM				?=			rm -f

all: $(TARGET)

$(TARGET):	$(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(TARGET)

re: fclean all
