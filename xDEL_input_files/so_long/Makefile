# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 16:28:02 by mmiilpal          #+#    #+#              #
#    Updated: 2024/04/30 16:28:05 by mmiilpal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
BONUS = so_long_bonus
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx  -lXext -lX11
LIBFTDIR = incs/libft/
MLX_DIR = incs/mlx/
OBJ_DIR = objs/
BONUS_OBJ_DIR = objs_bonus/
INC =-Iincs -Imlx -O3

LIBS = -L$(LIBFTDIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC = main.c graphic_manager.c moves.c parser.c init.c utils.c map_checker.c path_checker.c

SRCS := $(addprefix srcs/, $(SRC))
OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

BONUS_S := $(addprefix bonus_srcs/, $(SRC))
BONUS_OBJS = $(patsubst bonus_srcs/%.c,$(BONUS_OBJ_DIR)%.o,$(BONUS_S))

all: create_dirs $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -s -C  $(MLX_DIR)
	$(MAKE) -s -C $(LIBFTDIR)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME) $(MLX_FLAGS)

$(OBJS): $(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

bonus: create_dirs_b $(BONUS)

$(BONUS): $(BONUS_OBJS)
	$(MAKE) -s -C $(LIBFTDIR)
	$(MAKE) -s -C $(MLX_DIR)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS) $(MLX_FLAGS)

$(BONUS_OBJS): $(BONUS_OBJ_DIR)%.o: bonus_srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)

create_dirs_b:
	@mkdir -p $(BONUS_OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BONUS_OBJ_DIR)
	$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	$(MAKE) -s -C $(LIBFTDIR) fclean


re: clean all

.PHONY: all clean fclean create_dirs re

