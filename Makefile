# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 12:41:28 by mmiilpal          #+#    #+#              #
#    Updated: 2025/09/03 12:41:29 by mmiilpal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifneq ($(filter clean fclean, $(MAKECMDGOALS)),)
$(info Cleaning Cub3d 🚮)
else
$(info Compiling Cub3D 🎮)
endif

NAME = cub3d
BONUS = cub3d_bonus
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx  -lXext -lX11
LIBFTDIR = incs/libft/
MLX_DIR = incs/mlx/
OBJ_DIR = objs/
BONUS_OBJ_DIR = bonus/objs/
INC = -Iincs -Imlx -O3
BONUS_INC = -Ibonus/incs -Iincs -Imlx -O3

LIBS = -L$(LIBFTDIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -lft

SRC = main.c utils/error.c parser/parser.c parser/p_utils.c \
	parser/texture.c utils/free.c parser/map.c parser/map_bounds.c \
	parser/color.c parser/line.c parser/list_utils.c parser/parsing_utils.c init/init.c game_loop/game_loop.c \
	game_loop/move.c game_loop/render.c game_loop/render_utils.c game_loop/raycasting.c \
	game_loop/move_utils.c

BONUS_SRC = main.c utils/error.c utils/free.c utils/free_utils.c \
	parser/parser.c parser/p_utils.c parser/texture.c parser/map.c \
	parser/map_validation.c parser/map_utils.c parser/map_bounds.c \
	parser/color.c parser/line.c parser/list_utils.c parser/parsing_utils.c \
	init/init.c init/init_utils.c init/init_mlx.c init/init_textures.c \
	init/texture_utils.c game_loop/game_loop.c game_loop/game_loop_utils.c \
	game_loop/game_render_utils.c game_loop/game_arms.c game_loop/move.c \
	game_loop/move_utils.c game_loop/mouse.c game_loop/render.c \
	game_loop/render_utils.c game_loop/raycasting_utils.c \
	game_loop/render_draw.c game_loop/render_helpers.c chalk/wall_tag.c chalk/wall_tag_utils.c \
	minimap/minimap.c minimap/minimap_draw.c minimap/minimap_walls.c \
	minimap/minimap_player.c game_loop/move_helpers.c \
	minimap/minimap_blend.c minimap/minimap_render.c utils/free_textures.c \
	game_loop/mirror_utils.c pick_up/item_pick_up.c \
	pick_up/item_pick_up_helper.c utils/inventory_utils.c \
	sprites/chalk_init.c sprites/chalk_animation.c sprites/chalk_render.c \
	sprites/chalk_render2.c sprites/chalk_render3.c sprites/chalk_minimap.c \
	sprites/chalk_utils.c sprites/chalk_visibility.c doors/doors.c \
	doors/door_utils.c game_loop/mirror.c game_loop/game_loop_printer.c \
	thread/thread.c thread/time.c thread/thread_utils.c

SRCS := $(addprefix srcs/, $(SRC))
OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

BONUS_SRCS := $(addprefix bonus/srcs/, $(BONUS_SRC))
BONUS_OBJS = $(patsubst %.c,$(BONUS_OBJ_DIR)%.o,$(BONUS_SRCS))

all: create_dirs $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s -C  $(MLX_DIR)
	@$(MAKE) -s -C $(LIBFTDIR) && echo "Libft Compiled Successfully ✅"
	@$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME) $(MLX_FLAGS) && echo "Cub3D Compiled Successfully ✅"

$(OBJS): $(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

bonus: create_dirs_b $(BONUS)

$(BONUS): $(BONUS_OBJS)
	@$(MAKE) -s -C $(LIBFTDIR) && echo "Libft Compiled Successfully ✅"
	@$(MAKE) -s -C $(MLX_DIR)
	@$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS) $(MLX_FLAGS) && echo "Cub3D Bonus Compiled Successfully ✅"

$(BONUS_OBJS): $(BONUS_OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(BONUS_INC) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)

create_dirs_b:
	@mkdir -p $(BONUS_OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BONUS_OBJ_DIR)
	@$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)
	@$(MAKE) -s -C $(LIBFTDIR) fclean


re: clean all

.PHONY: all clean fclean create_dirs re

