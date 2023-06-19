##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## make all
##

TARGET_server			=			zappy_server
TARGET_server_DIR		=			src/SERVER
TARGET_gui				=			zappy_gui
TARGET_gui_DIR			=			src/GUI
TARGET_ai				=			zappy_ai
TARGET_ai_DIR			=			src/AI

CP						?=			cp
RM						?=			rm -f

all: $(TARGET_server) $(TARGET_gui) $(TARGET_ai)

# ----------------------------------------------------------------------------
# TARGET
# ----------------------------------------------------------------------------

$(TARGET_server):	$(TARGET_server_DIR)
	$(MAKE) -C $(TARGET_server_DIR)
	$(CP) $(TARGET_server_DIR)/$(TARGET_server) $(TARGET_server)

$(TARGET_gui):		$(TARGET_gui_DIR)
	cmake -S $(TARGET_gui_DIR) -B $(TARGET_gui_DIR)/build
	$(MAKE) -C $(TARGET_gui_DIR)/build
	$(CP) $(TARGET_gui_DIR)/$(TARGET_gui) $(TARGET_gui)

$(TARGET_ai):		$(TARGET_ai_DIR)
	$(MAKE) -C $(TARGET_ai_DIR)
	$(CP) $(TARGET_ai_DIR)/$(TARGET_ai) $(TARGET_ai)

# ----------------------------------------------------------------------------
# CLEAN
# ----------------------------------------------------------------------------

$(TARGET_server)_clean:
	$(MAKE) -C $(TARGET_server_DIR) clean

$(TARGET_gui)_clean:
	if [ -d $(TARGET_gui_DIR)/build ]; then \
		$(RM) -r $(TARGET_gui_DIR)/build; \
	fi

$(TARGET_ai)_clean:
	$(MAKE) -C $(TARGET_ai_DIR) clean

clean:				$(TARGET_server)_clean
clean:				$(TARGET_gui)_clean
clean:				$(TARGET_ai)_clean

$(TARGET_server)_fclean:	$(TARGET_server)_clean
	$(MAKE) -C $(TARGET_server_DIR) fclean

$(TARGET_gui)_fclean:		$(TARGET_gui)_clean

$(TARGET_ai)_fclean:		$(TARGET_ai)_clean
	$(MAKE) -C $(TARGET_ai_DIR) fclean

fclean:				clean
fclean:				$(TARGET_server)_fclean
fclean:				$(TARGET_gui)_fclean
fclean:				$(TARGET_ai)_fclean
	$(RM) $(TARGET_server)
	$(RM) $(TARGET_gui)
	$(RM) $(TARGET_ai)

# ----------------------------------------------------------------------------
# RE
# ----------------------------------------------------------------------------

re:					fclean all

# ----------------------------------------------------------------------------
# TESTS
# ----------------------------------------------------------------------------

tests_run: fclean
	$(MAKE) -C $(TARGET_server_DIR) tests_run
