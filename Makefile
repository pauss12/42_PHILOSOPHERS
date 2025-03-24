# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmendez- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 20:03:59 by pmendez-          #+#    #+#              #
#    Updated: 2025/03/24 20:04:00 by pmendez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
CURRENT_FILE = 0
TOTAL_FILES = $(words $(FILES))
CLEAN_SHELL = \033[2K\r


NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address,leak,undefined

FILES = src/philo.c \
		src/check_args_start.c \
		src/treat_memory.c \

OBJS = $(FILES:.c=.o)

all: show_progress $(NAME)

$(NAME): $(OBJS) include/philo.h
	@make -s -C libft
	@$(CC) $(FILES) -L libft -lft -o $(NAME)
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
	@make fclean -C libft
	@echo "Cleaning finished! 🧹"

fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C libft
	@echo " Deleting finished! 🗑"

re: fclean all

.PHONY: all clean fclean re upload norm
