##
## EPITECH PROJECT, 2023
## zappy
## File description:
## server
##

TARGET			=			zappy_server

LIBS_DIR		=			./libs

CFLAGS			=			-Wall \
							-Wextra \
							-Wpedantic \
							-Iinclude \
							-Ilibs/tinylibc/includes \
							-Ilibs/circularbuffer/includes
LDFLAGS			=			-L $(LIBS_DIR)/tinylibc/ -l tinylibc	\
							-L $(LIBS_DIR)/circularbuffer/ -l circularbuffer

SRC				=												\
							src/network/ntw_destroy.c			\
							src/network/ntw_init.c				\
							src/network/ntw_wait_till_events.c	\
							src/main.c

OBJ				=			$(SRC:.c=.o)

RM				?=			rm -f

all: $(LIBS_DIR)/tinylibc/libtinylibc.a
all: $(LIBS_DIR)/circularbuffer/libcircularbuffer.a
all: $(TARGET)

$(TARGET):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

$(LIBS_DIR)/tinylibc/libtinylibc.a:
	$(MAKE) -C $(LIBS_DIR)

$(LIBS_DIR)/circularbuffer/libcircularbuffer.a:
	$(MAKE) -C $(LIBS_DIR)

$(LIBS_DIR)_clean:
	$(MAKE) -C $(LIBS_DIR) clean

clean: $(LIBS_DIR)_clean
	$(RM) $(OBJ)

$(LIBS_DIR)_fclean:
	$(MAKE) -C $(LIBS_DIR) fclean

fclean: clean $(LIBS_DIR)_fclean
	$(RM) $(TARGET)

re: fclean all
