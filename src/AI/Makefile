##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ai
##

TARGET		=		zappy_ai

PIP_TARGET	=		zappy_ia

CP			?=		cp
RM			?=		rm -f
TOEXEC		?=		chmod +x

all: $(TARGET)

$(TARGET):
	pip install --user .
	$(CP) "$(TARGET).py" "$(TARGET)"
	$(TOEXEC) "$(TARGET)"

clean:
	rm -rf "__pycache__"

fclean:
	pip uninstall -y $(PIP_TARGET)
	$(RM) $(TARGET)

re: fclean all
