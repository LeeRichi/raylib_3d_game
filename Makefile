# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 17:46:27 by wweerasi          #+#    #+#              #
#    Updated: 2025/07/10 19:31:38 by wweerasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

DIR_MLX			= ./lib/MLX42
DIR_LIBFT		= ./lib/libft
DIR_SRC			= ./src
DIR_SRC_BONUS	= ./src_bonus
DIR_OBJ			= $(DIR_SRC)/objects
DIR_OBJ_BONUS	= $(DIR_SRC_BONUS)/objects_bonus
DIR_INC			= ./includes
HEADERS			= $(DIR_INC)/cub3D.h
HEADERS_BONUS	= $(DIR_INC)/cub3D_bonus.h
MLX42_REPO		= https://github.com/codam-coding-college/MLX42.git

SRC =	main.c \
		parse_map/parse_map.c \
		parse_map/parse_map_helper.c \
		parse_map/parse_map_helper_2.c \
		parse_map/save_texture.c \
		parse_map/save_color.c \
		parse_map/save_map.c \
		map_checker/map_checker.c \
		map_checker/map_checker_helper.c \
		map_checker/flood_fill_n_utils.c \
		utils.c \
		clean.c \
		inits/game_init.c \
		inits/player_init.c \
		render/render.c \
		render/render_helper.c \
		render/render_pause.c \
		handler/key_handler.c \
		handler/key_handler_helper.c \
		handler/mouse_handler.c \

SRC_BONUS =	main.c \
			parse_map/parse_map.c \
			parse_map/parse_map_helper.c \
			parse_map/parse_map_helper_2.c \
			parse_map/save_texture.c \
			parse_map/save_color.c \
			parse_map/save_map.c \
			map_checker/map_checker.c \
			map_checker/map_checker_helper.c \
			map_checker/flood_fill_n_utils.c \
			utils.c \
			clean.c \
			inits/game_init.c \
			inits/player_init.c \
			render/render.c \
			render/render_helper.c \
			render/render_pause.c \
			render/render_minimap.c \
			handler/key_handler.c \
			handler/key_handler_helper.c \
			handler/mouse_handler.c \

OBJECTS			= $(addprefix $(DIR_OBJ)/,$(SRC:.c=.o))
OBJECTS_BONUS 	= $(addprefix $(DIR_OBJ_BONUS)/,$(SRC_BONUS:.c=.o))

LIBMLX			= $(DIR_MLX)/build/libmlx42.a

LIBMLX_FLAGS	= $(LIBMLX) -ldl -lglfw -lm
LIBFT_FLAGS		= -L $(DIR_LIBFT) -lft

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf

all: libft $(LIBMLX) $(NAME)
bonus: libft $(LIBMLX) .bonus
libft:
	@make -C $(DIR_LIBFT)

$(LIBMLX):
	@if [ ! -d $(DIR_MLX) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git \
		$(DIR_MLX); \
	fi
	@if [ ! -f $(DIR_MLX)/build/libmlx42.a ]; then \
		cmake $(DIR_MLX) -B $(DIR_MLX)/build && make -C $(DIR_MLX)/build -j4; \
	fi

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -o $@

.bonus: $(OBJECTS_BONUS)
	$(CC) $(OBJECTS_BONUS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -o $(NAME)_bonus
	@touch .bonus

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ_BONUS)/%.o: $(DIR_SRC_BONUS)/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@


clean:
	@$(RM) $(DIR_OBJ) 
	@$(RM) $(DIR_OBJ_BONUS)
	@$(RM) $(DIR_MLX)/build
	@make -C $(DIR_LIBFT) clean

fclean: clean
	$(RM) .bonus
	@$(RM) $(NAME) 
	@$(RM) $(NAME)_bonus
	@$(RM) $(DIR_MLX)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all bonus libft clean fclean re