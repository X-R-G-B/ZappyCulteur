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

# ----------------------------------------------------------------------------
# SRC
# ----------------------------------------------------------------------------


# ARGS -----------------------------------------------------------------------
SRC_ARGS		:=															\
							args_debug.c									\
							args_destroy.c									\
							args_init.c
SRC_ARGS		:=			$(addprefix args/, $(SRC_ARGS))

# CLIENT ---------------------------------------------------------------------
SRC_CLIENT		:=															\
							client_destroy.c								\
							client_init.c
SRC_CLIENT		:=			$(addprefix client/, $(SRC_CLIENT))


# LOOP -----------------------------------------------------------------------
SRC_LOOP_AICMD	=															\
							update_ai_cmd.c
SRC_LOOP_AICMD	:=			$(addprefix ai_cmd/, $(SRC_LOOP_AICMD))

SRC_LOOP_GRCMD	=															\
							cmd_msz.c										\
							update_graphic_cmd.c
SRC_LOOP_GRCMD	:=			$(addprefix graphic_cmd/, $(SRC_LOOP_GRCMD))

SRC_LOOP_CONN	=															\
							$(SRC_LOOP_AICMD)								\
							$(SRC_LOOP_GRCMD)								\
							update.c
SRC_LOOP_CONN	:=			$(addprefix state_connected/, $(SRC_LOOP_CONN))

SRC_LOOP		:=															\
							$(SRC_LOOP_CONN)								\
							loop.c											\
							update_client_not_connected.c					\
							update_client_waiting_team_name.c
SRC_LOOP		:=			$(addprefix loop/, $(SRC_LOOP))

# ----------------------------------------------------------------------------
# network
# ----------------------------------------------------------------------------
SRC_NTW			:=															\
							internal_read_command.c							\
							internal_remove_client_clean.c					\
							internal_write_command.c						\
							ntw_client_destroy.c							\
							ntw_client_init.c								\
							ntw_destroy.c									\
							ntw_init.c										\
							ntw_loop.c										\
							ntw_wait_till_events.c
SRC_NTW			:=			$(addprefix network/, $(SRC_NTW))

# ----------------------------------------------------------------------------
# SRC
# ----------------------------------------------------------------------------
SRC				:=															\
							$(SRC_ARGS)										\
							$(SRC_CLIENT)									\
							$(SRC_LOOP)										\
							$(SRC_NTW)										\
							get_id.c										\
							main.c											\
							on_new_conn.c
SRC				:=			$(addprefix src/, $(SRC))

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
