# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 20:03:59 by pmendez-          #+#    #+#              #
#    Updated: 2025/10/12 18:28:53 by pmendez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
CURRENT_FILE = 0
TOTAL_FILES = $(words $(FILES))
CLEAN_SHELL = \033[2K\r.

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_DIR = obj

DEBUG ?=

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=thread
endif

FILES = src/philo.c \
		src/check_args_start.c \
		src/treat_memory.c \
		src/routine.c \
		src/utils_threads.c \
		src/create_threads.c \
		src/utils.c \
		src/utils2.c \
		src/utils_print.c \
		src/fork_treatment.c \
		src/itoa_join_long.c \
		src/values_parsing.c

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(FILES:.c=.o)))

all: show_progress $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) include/philo.h
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "$(CLEAN_SHELL) $(GREEN)\n 🚀 Compilation finished! $(NC)👍"

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "$(CLEAN_SHELL) 🚀 Compiling $<... $(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES))))%%"
	@$(CC) $(CFLAGS) -c $< -o $@

show_progress:
	@if [ -f $(NAME) ]; then \
		echo "$(GREEN)The compiled code is already updated.$(NC)"; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Cleaning finished! 🧹"

fclean: clean
	@rm -f $(NAME)
	@echo " Deleting finished! 🗑"

norminette:
	@norminette src/*.c src/*.h

re: fclean all

.PHONY: all clean fclean re norminette show_progress
