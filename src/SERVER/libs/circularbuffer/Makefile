##
## EPITECH PROJECT, 2023
## MyTeams
## File description:
## circular buffer lib
##

TARGET		:=		libcircularbuffer.a

SRC			:=		src/create.c		\
					src/destroy.c		\
					src/read.c			\
					src/read_multiple.c	\
					src/write.c			\
					src/empty.c

OBJ			:=		$(SRC:.c=.o)

CFLAGS		:=		-Wall -Wextra -Wpedantic -Iincludes -I../tinylibc/includes

all: $(TARGET)

$(TARGET): 	$(OBJ)
	ar rc $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
