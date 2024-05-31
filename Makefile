PROJECT_NAME = PMergeMe

NAME = pmergeme

SRC_FILES = $(shell find src -type f -name "*.cpp" | sed 's/src\///g')

SRC_DIR = src

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = objs
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

DEP_DIR = deps
DEP_FILES = $(addprefix $(DEP_DIR)/, $(SRCS:.cpp=.d))

INCLUDES = -Iincludes -I.
#LIBS =

CC = c++

DEBUG = true

### COLORS ###

RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[93m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[96m
ORANGE = \033[0;33m
RESET = \033[0m

CFLAGS = \
		$(INCLUDES) \
		-std=c++98 \
		-Wall -Wextra -Werror \
		-MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d \
		-Wall -Wextra -Werror \
		-DCOLORS_RED="\"$(RED)\"" \
		-DCOLORS_GREEN="\"$(GREEN)\"" \
		-DCOLORS_YELLOW="\"$(YELLOW)\"" \
		-DCOLORS_BLUE="\"$(BLUE)\"" \
		-DCOLORS_MAGENTA="\"$(MAGENTA)\"" \
		-DCOLORS_CYAN="\"$(CYAN)\"" \
		-DCOLORS_ORANGE="\"$(ORANGE)\"" \
		-DCOLORS_RESET="\"$(RESET)\""

ifeq ($(DEBUG), true)
	CFLAGS += -g -gdwarf-2 -g3 -DDEBUG #-fsanitize=address,undefined
else
	CFLAGS += -O3
endif


TAG = [$(CYAN)$(PROJECT_NAME)$(RESET)]

### END OF COLORS ###

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(TAG) linking $(YELLOW)$@$(RESET).."
	@$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIBS)
	@echo "$(TAG) done$(RESET)!"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR) $(DEP_DIR)
	@echo "$(TAG) compiling $(YELLOW)$<$(RESET).."
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.d)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@
$(DEP_DIR):
	@mkdir -p $@

$(DEP_FILES):

include $(wildcard $(DEP_FILES))

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(DEP_DIR)
	@echo "$(TAG) cleaned $(YELLOW)objects$(RESET)!"

fclean: clean
	@rm -f $(NAME)
	@echo "$(TAG) cleaned $(YELLOW)executable$(RESET)!"


re: fclean
	@make $(MAKE_MT) all --jobs=$(shell nproc) --output-sync=target --no-print-directory

watch:
	@while true; do \
		make $(MAKE_MT) all --no-print-directory --no-print; \
		inotifywait -qre close_write --exclude ".*\.d" $(SRCS) $(INCLUDES); \
		echo "$(TAG) $(YELLOW)recompiling$(RESET).."; \
	done

.PHONY: all clean fclean re
