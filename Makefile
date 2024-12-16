# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quentin <quentin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 12:20:34 by qmorinea          #+#    #+#              #
#    Updated: 2024/12/16 15:30:05 by quentin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_INC)

# Directories
SRC_DIR = src/mandatory
BONUS_DIR = src/bonus
OBJ_DIR = obj/mandatory
OBJ_BONUS_DIR = obj/bonus
OBJ_FOLDER = obj
LIBFT_DIR = libft

# Name
NAME = pipex
NAME_BONUS = pipex_bonus

LIBFT = $(LIBFT_DIR)/libft.a

# Header
INC = includes/mandatory
INC_BONUS = includes/bonus
LIBFT_INC = libft/includes
MLX_INC = minilibx-linux

# Source and Object files
SRC_LIST = main.c\
			parsing.c\
			free.c\
			path.c\
			child.c\
			exec.c

# Source and Object files BONUS
BONUS_LIST = 

SRC = $(addprefix $(SRC_DIR)/,$(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_LIST:.c=.o))
SRC_BONUS = $(addprefix $(BONUS_DIR)/,$(BONUS_LIST))
OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR)/,$(BONUS_LIST:.c=.o))

# Colors
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Main
all: $(OBJ_DIR) $(NAME)

# Create path for object
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

# Linking object files
$(NAME): $(MLX_LIB) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(INC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(YELLOW)Exec $(NAME) created.$(RESET)"

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(LIBFT_INC)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
# Compile bonus source files to object files
$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c $(INC_BONUS) $(LIBFT_INC)
	@$(CC) $(CFLAGS) -I $(INC_BONUS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

clean:
	@rm -rf $(OBJ_FOLDER)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)Pipex: Cleaned object files$(RESET)"

fclean:
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf $(OBJ_FOLDER)
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)Pipex: Removed binary files$(RESET)"

re: fclean all

bonus: $(OBJ_BONUS_DIR) $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) -I $(INC_BONUS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(YELLOW)BONUS : Exec $(NAME) created.$(RESET)"
ARG1 = Makefile
ARG2 = ls blou
ARG2_2 = "$(ARG2)"
ARG3 = grep pipe
ARG3_2 = "$(ARG3)"
ARG4 = out1
ARG4_2 = out2
test: all
	-./$(NAME) $(ARG1) $(ARG2_2) $(ARG3_2) $(ARG4)
	echo $$?

test2:
	-< $(ARG1) $(ARG2) | $(ARG3) > $(ARG4_2)
	echo $$?

leak:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./$(NAME) Makefile "ls -la" "grep pipe" out

.PHONY: all clean fclean re bonus