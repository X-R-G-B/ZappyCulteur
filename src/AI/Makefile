##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ai
##

TARGET		=		zappy_ai

PIP_TARGET	=		zappy_ia

PIP_DEPS	=						\
					pandas			\
					scikit_learn	\
					numpy			\
					joblib			\
					setuptools		\
					wheel			\
					pip

PIP_DEPS_RM	:=		$(filter-out pip, $(PIP_DEPS))
PIP_DEPS_RM	:=		$(filter-out setuptools, $(PIP_DEPS_RM))
PIP_DEPS_RM	:=		$(filter-out wheel, $(PIP_DEPS_RM))

LOCAL_DEPS	=		local_deps

CP			?=		cp
RM			?=		rm -f
TOEXEC		?=		chmod +x

all: $(TARGET)

$(LOCAL_DEPS)/requirements.txt:
	echo "$(PIP_DEPS)" > ./$(LOCAL_DEPS)/requirements.txt
	sed -i "s/ /\n/g" ./$(LOCAL_DEPS)/requirements.txt

$(LOCAL_DEPS)/simple: $(LOCAL_DEPS)/requirements.txt
	$(MAKE) $(LOCAL_DEPS)/simple-force

$(LOCAL_DEPS)/simple-force: $(LOCAL_DEPS)/requirements.txt
	pip install --user piprepo
	pip download -d ./local_deps -r ./$(LOCAL_DEPS)/requirements.txt
	piprepo build ./local_deps

$(TARGET): $(LOCAL_DEPS)/simple
	pip install --user -i ./local_deps/simple .
	$(CP) "$(TARGET).py" "$(TARGET)"
	$(TOEXEC) "$(TARGET)"

clean:
	$(RM) -r "__pycache__"
	$(RM) -r $(PIP_TARGET).egg-info

fclean: clean
	pip uninstall -y $(PIP_TARGET) $(PIP_DEPS_RM)
	$(RM) $(LOCAL_DEPS)/requirements.txt
	pip uninstall -y piprepo || true
	$(RM) $(TARGET)

fclean-simple: fclean
	$(RM) -r $(LOCAL_DEPS)/simple
	$(RM) $(LOCAL_DEPS)/*.whl

re: fclean all

re-simple: fclean-simple $(LOCAL_DEPS)/simple all
