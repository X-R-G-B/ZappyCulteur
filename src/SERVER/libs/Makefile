##
## EPITECH PROJECT, 2023
## zappy server lib
## File description:
## make
##

TARGET_tinylibc_DIR		=	tinylibc
TARGET_circular_DIR		=	circularbuffer

all: $(TARGET_tinylibc_DIR)/libtinylibc.a
all: $(TARGET_circular_DIR)/libcircularbuffer.a

$(TARGET_tinylibc_DIR)/libtinylibc.a:
	$(MAKE) -C $(TARGET_tinylibc_DIR)

$(TARGET_circular_DIR)/libcircularbuffer.a:
	$(MAKE) -C $(TARGET_circular_DIR)

$(TARGET_tinylibc_DIR)_clean:
	$(MAKE) -C $(TARGET_tinylibc_DIR) clean

$(TARGET_circular_DIR)_clean:
	$(MAKE) -C $(TARGET_circular_DIR) clean

clean: $(TARGET_tinylibc_DIR)_clean
clean: $(TARGET_circular_DIR)_clean

$(TARGET_tinylibc_DIR)_fclean:
	$(MAKE) -C $(TARGET_tinylibc_DIR) fclean

$(TARGET_circular_DIR)_fclean:
	$(MAKE) -C $(TARGET_circular_DIR) fclean

fclean: clean
fclean: $(TARGET_tinylibc_DIR)_fclean
fclean: $(TARGET_circular_DIR)_fclean

re: fclean all
