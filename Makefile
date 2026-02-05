# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 13:51:40 by tjkruger          #+#    #+#              #
#    Updated: 2025/06/09 13:51:40 by tjkruger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS	= -Wall -Wextra -Werror

NAME	= philo
CC		= cc



SRC_DIR = ./src
UTILS_DIR = ./utils
PRINTF_DIR = ./printf
OBJ_DIR = ./obj

SRC		= 	$(SRC_DIR)/fork_management.c \
			$(SRC_DIR)/initialization.c \
			$(SRC_DIR)/input_validation.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/monitor_routine.c \
			$(SRC_DIR)/output.c \
			$(SRC_DIR)/philosopher_actions.c \
			$(SRC_DIR)/philosopher_routine.c \
			$(SRC_DIR)/state_management.c \
			$(SRC_DIR)/thread_management.c \
			$(UTILS_DIR)/ft_advanced_atoi.c \
			$(UTILS_DIR)/clock.c \
			$(UTILS_DIR)/utils_string.c \


OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
