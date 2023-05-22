##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ai
##

TARGET		=		zappy_ai

CP			?=		cp
RM			?=		rm -f
TOEXEC		?=		chmod +x

all: $(TARGET)

$(TARGET):
	$(CP) "$(TARGET).py" "$(TARGET)"
	$(TOEXEC) "$(TARGET)"

clean:
	rm -rf "__pycache__"

fclean:
	$(RM) $(TARGET)

re: fclean all
