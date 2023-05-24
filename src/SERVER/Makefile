##
## EPITECH PROJECT, 2023
## zappy
## File description:
## server
##

TARGET			=			zappy_server

LIBS_DIR		=			./libs

CFLAGS			=															\
							-Wall											\
							-Wextra											\
							-Wpedantic										\
							-Iinclude										\
							-Ilibs/tinylibc/includes						\
							-Ilibs/circularbuffer/includes

LDFLAGS			=															\
							-L $(LIBS_DIR)/circularbuffer/					\
							-l circularbuffer								\
							-L $(LIBS_DIR)/tinylibc/						\
							-l tinylibc

SRC				=															\
							src/client/client_destroy.c						\
							src/client/client_init.c						\
							src/loop/state_connected/update.c				\
							src/loop/loop.c									\
							src/loop/update_client_not_connected.c			\
							src/loop/update_client_waiting_team_name.c		\
							src/args/args_debug.c							\
							src/args/args_destroy.c							\
							src/args/args_init.c							\
							src/network/internal_read_command.c				\
							src/network/internal_remove_client_clean.c		\
							src/network/internal_write_command.c			\
							src/network/ntw_client_destroy.c				\
							src/network/ntw_client_init.c					\
							src/network/ntw_destroy.c						\
							src/network/ntw_init.c							\
							src/network/ntw_loop.c							\
							src/network/ntw_wait_till_events.c				\
							src/get_id.c									\
							src/main.c										\
							src/on_new_conn.c

OBJ				=			$(SRC:.c=.o)

RM				?=			rm -f

all: $(LIBS_DIR)/tinylibc/libtinylibc.a
all: $(LIBS_DIR)/circularbuffer/libcircularbuffer.a
all: $(TARGET)

$(TARGET):												$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

$(LIBS_DIR)/tinylibc/libtinylibc.a:						$(LIBS_DIR)
	$(MAKE) -C $(LIBS_DIR)

$(LIBS_DIR)/circularbuffer/libcircularbuffer.a:			$(LIBS_DIR)
	$(MAKE) -C $(LIBS_DIR)

$(LIBS_DIR)_clean:										$(LIBS_DIR)
	$(MAKE) -C $(LIBS_DIR) clean

clean:													$(LIBS_DIR)_clean
	$(RM) $(OBJ)

$(LIBS_DIR)_fclean:										$(LIBS_DIR)
	$(MAKE) -C $(LIBS_DIR) fclean

fclean:													clean
fclean:													$(LIBS_DIR)_fclean
	$(RM) $(TARGET)

re:														fclean
re:														all
