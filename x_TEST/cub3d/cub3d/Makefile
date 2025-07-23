# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 00:00:00 by mmiilpal          #+#    #+#              #
#    Updated: 2025/07/22 15:59:10 by mmiilpal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = cub3d

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L./mlx -lmlx_Linux -lXext -lX11 -lm -lz

# Directories
MLX_DIR = mlx
SRC_DIR = .
OBJ_DIR = obj

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# MLX library
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Default target
all: $(MLX_LIB) $(NAME)

# Build the main program
$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# Build MLX library
$(MLX_LIB):
	@echo "$(BLUE)Building MLX library...$(RESET)"
	@make -C $(MLX_DIR) --silent
	@echo "$(GREEN)✓ MLX library built!$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean --silent

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

# Run the program
run: $(NAME)
	@echo "$(GREEN)Running $(NAME)...$(RESET)"
	@./$(NAME)

# Debug build
debug: CFLAGS += -fsanitize=address -g3
debug: re

# Install dependencies (if needed)
install:
	@echo "$(BLUE)Installing dependencies...$(RESET)"
	@sudo apt-get update && sudo apt-get install -y libx11-dev libxext-dev libbsd-dev

# Help
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and executable"
	@echo "  re      - Clean and rebuild everything"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug flags and AddressSanitizer"
	@echo "  install - Install required system dependencies"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all clean fclean re run debug install help
