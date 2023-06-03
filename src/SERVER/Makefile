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
							-Wfor-loop-analysis								\
							-Iinclude										\
							-Ilibs/tinylibc/includes						\
							-Ilibs/circularbuffer/includes					\
							-MMD											\
							-O2

LDFLAGS			=															\
							-L $(LIBS_DIR)/circularbuffer/					\
							-l circularbuffer								\
							-L $(LIBS_DIR)/tinylibc/						\
							-l tinylibc

ECHO			=			echo -e

# ----------------------------------------------------------------------------
# Colors
# ----------------------------------------------------------------------------

CYAN				:=		'\033[1;36m'
BLUE				:=		'\033[1;34m'
GREEN				:=		'\033[1;32m'
RESET				:=		'\033[0m'

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
							cmd_broadcast.c									\
							cmd_eject.c										\
							cmd_fork.c										\
							cmd_forward.c									\
							cmd_inventory.c									\
							cmd_invocation.c								\
							cmd_left.c										\
							cmd_look.c										\
							cmd_right.c										\
							cmd_set.c										\
							cmd_take.c										\
							update_ai_cmd.c
SRC_LOOP_AICMD	:=			$(addprefix ai_cmd/, $(SRC_LOOP_AICMD))

SRC_LOOP_GRCMD	=															\
							cmd_bct.c										\
							cmd_mct.c										\
							cmd_msz.c										\
							cmd_ppo.c										\
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

# MAP ------------------------------------------------------------------------
SRC_MAP		:=																\
							map_add_ressources.c							\
							map_destroy.c									\
							map_index_i_to_x_y.c							\
							map_init.c
SRC_MAP		:=				$(addprefix map/, $(SRC_MAP))

# NETWORK --------------------------------------------------------------------
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

# TRANTORIEN -----------------------------------------------------------------
SRC_TRNT_BRO	:=															\
							incantation_start.c
SRC_TRNT_BRO	:=			$(addprefix broadcasts/, $(SRC_TRNT_BRO))

SRC_TRNT_CMD	:=															\
							command_set_object_down.c						\
							command_incantation.c							\
							command_take_object.c							\
							command_look_around.c							\
							command_look_around_sides.c						\
							command_look_around_utils.c						\
							command_inventory.c								\
							command_move.c									\
							command_turn.c
SRC_TRNT_CMD	:=			$(addprefix commands/, $(SRC_TRNT_CMD))

SRC_TRNT		:=															\
							$(SRC_TRNT_BRO)									\
							$(SRC_TRNT_CMD)									\
							action_destroy.c								\
							action_init.c									\
							trantorien_add_act.c							\
							trantorien_add_act_broadcast.c					\
							trantorien_add_act_set.c						\
							trantorien_add_act_take.c						\
							trantorien_destroy.c							\
							trantorien_init.c								\
							trantorien_is_cmd_availible.c					\
							trantorien_place_cmd.c							\
							trantorien_reduce_freq.c
SRC_TRNT		:=			$(addprefix trantorien/, $(SRC_TRNT))

# ----------------------------------------------------------------------------
# SRC
# ----------------------------------------------------------------------------
SRC				:=															\
							$(SRC_ARGS)										\
							$(SRC_CLIENT)									\
							$(SRC_LOOP)										\
							$(SRC_MAP)										\
							$(SRC_NTW)										\
							$(SRC_TRNT)										\
							get_id.c										\
							main.c											\
							on_new_conn.c									\
							zappy_destroy.c									\
							zappy_find_trantorien_by_id.c					\
							zappy_init.c
SRC				:=			$(addprefix src/, $(SRC))

OBJ				:=			$(SRC:.c=.o)
DEP				:=			$(SRC:.c=.d)

RM				?=			rm -f

CC				=			clang

all: $(LIBS_DIR)/tinylibc/libtinylibc.a
all: $(LIBS_DIR)/circularbuffer/libcircularbuffer.a
all: $(TARGET)

all_fast:
	@$(MAKE) -j --no-print-directory -C . all

$(TARGET):												$(OBJ)
	@$(ECHO) $(CYAN)'==< CFLAGS >==:'$(RESET) '$(CFLAGS)'
	@$(ECHO) $(CYAN)'==< LDFLAGS >==:'$(RESET) '$(LDFLAGS)'
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)
	@$(ECHO) $(CYAN)'==< COMPILED >==:'$(RESET) $(GREEN)$(TARGET)$(RESET)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) $(GREEN)$@$(RESET) '<-' $(CYAN)$<$(RESET)

$(TARGET)_fast:
	@$(MAKE) -j --no-print-directory -C . $(TARGET)

$(LIBS_DIR)/tinylibc/libtinylibc.a:						$(LIBS_DIR)
	@$(MAKE) -j --no-print-directory -C $(LIBS_DIR) 1>/dev/null

$(LIBS_DIR)/circularbuffer/libcircularbuffer.a:			$(LIBS_DIR)
	@$(MAKE) -j --no-print-directory -C $(LIBS_DIR) 1>/dev/null

$(LIBS_DIR)_clean:										$(LIBS_DIR)
	@$(MAKE) --no-print-directory -C $(LIBS_DIR) clean 1>/dev/null

clean:													$(LIBS_DIR)_clean
	@$(RM) $(OBJ) $(SRC:.c=.d)
	@$(ECHO) $(CYAN)'==< CLEANED >==:'$(RESET)

$(LIBS_DIR)_fclean:										$(LIBS_DIR)
	@$(MAKE) --no-print-directory -C $(LIBS_DIR) fclean 1>/dev/null

fclean:													clean
fclean:													$(LIBS_DIR)_fclean
	@$(RM) $(TARGET)
	@$(ECHO) $(CYAN)'==< FCLEANED >==:'$(RESET)

re:														fclean
re:														all

-include $(DEP)
