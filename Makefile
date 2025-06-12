# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 20:03:59 by pmendez-          #+#    #+#              #
#    Updated: 2025/06/12 22:27:42 by pmendez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
CURRENT_FILE = 0
TOTAL_FILES = $(words $(FILES))
CLEAN_SHELL = \033[2K\r

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=thread


FILES = src/philo.c \
		src/checkArgsStart.c \
		src/treatMemory.c \
		src/routine.c \
		src/utilsThreads.c \
		src/createThreads.c \
		src/utils.c \
		src/utils2.c \
		src/utilsPrint.c \
		src/forkTreatment.c

OBJS = $(FILES:.c=.o)

all: show_progress $(NAME)

$(NAME): $(OBJS) src/philo.h
	@$(CC) $(FILES) -o $(NAME)
	@echo "$(CLEAN_SHELL) $(GREEN)\n 🚀 Compilation finished! $(NC)👍"

%.o: %.c
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "$(CLEAN_SHELL) 🚀 Compiling $<... $(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES))))%%"
	@$(CC) $(CFLAGS) -c $< -o $@

show_progress:
	@if [ -f $(NAME) ]; then \
		echo "$(GREEN)The compiled code is already updated.$(NC)"; \
	fi

clean:
	@rm -f $(OBJS)
	@echo "Cleaning finished! 🧹"

fclean: clean
	@rm -f $(NAME)
	@echo " Deleting finished! 🗑"

run: $(NAME)
	@./$(NAME) 4 3 3 3 3

re: fclean all

.PHONY: all clean fclean re
