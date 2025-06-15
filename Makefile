# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 18:09:12 by chlee2            #+#    #+#              #
#    Updated: 2025/06/15 17:00:55 by chlee2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = lib/libft
LIBFT = $(LIBFTDIR)/libft.a

MLX42DIR = lib/MLX42
MLX42 = $(MLX42DIR)/build/libmlx42.a
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c \
		src/parse_map/parse_map.c \
		src/parse_map/save_texture.c \
		src/parse_map/save_color.c \
		src/parse_map/save_map.c \
		src/map_checker/map_checker.c \
		src/utils.c \
		src/clean.c \
		src/inits/game_init.c \
		src/inits/player_init.c \
		src/render/render.c \
		src/handler/key_handler.c \
		src/handler/mouse_handler.c \

OBJS = $(SRCS:.c=.o)

all: $(MLX42DIR) $(NAME)

$(MLX42DIR):
	git clone $(MLX42_REPO) $(MLX42DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft -L$(MLX42DIR)/build -lmlx42 -lglfw -lm

$(LIBFT):
	@make -C $(LIBFTDIR)

$(MLX42):
	@cmake -B $(MLX42DIR)/build -S $(MLX42DIR)
	@cmake --build $(MLX42DIR)/build

clean:
	$(RM) $(OBJS)
	@make clean -C $(LIBFTDIR)
	rm -rf $(MLX42DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re


