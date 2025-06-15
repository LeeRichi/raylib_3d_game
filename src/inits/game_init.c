/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:44:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 16:58:17 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void game_init(t_game *game)
{
	game->mlx = mlx_init(1920, 1080, "cub3D", true);
	if (!game->mlx)
	{
		printf("Error: mlx_init failed");
		exit(EXIT_FAILURE);
	}

	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);

	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
	{
		printf("Error: malloc failed for textures\n");
		exit(EXIT_FAILURE);
	}

	game->textures->n_wall_texture = mlx_load_png("./assets/Photoreal_Ice_05-512x512.png");
	game->textures->e_wall_texture = mlx_load_png("./assets/Photoreal_Ice_06-512x512.png");
	game->textures->s_wall_texture = mlx_load_png("./assets/Photoreal_Ice_07-512x512.png");
	game->textures->w_wall_texture = mlx_load_png("./assets/Photoreal_Ice_08-512x512.png");
	if (!game->textures->n_wall_texture || !game->textures->e_wall_texture || !game->textures->s_wall_texture || !game->textures->w_wall_texture)
	{
		printf("Error: mlx_load_png failed\n");
		exit(EXIT_FAILURE);
	}

	game->textures->n_wall_img = mlx_texture_to_image(game->mlx, game->textures->n_wall_texture);
	game->textures->e_wall_img = mlx_texture_to_image(game->mlx, game->textures->e_wall_texture);
	game->textures->s_wall_img = mlx_texture_to_image(game->mlx, game->textures->s_wall_texture);
	game->textures->w_wall_img = mlx_texture_to_image(game->mlx, game->textures->w_wall_texture);
	if (!game->textures->n_wall_img || !game->textures->e_wall_img || !game->textures->s_wall_img || !game->textures->w_wall_img)
	{
		printf("Error: mlx_texture_to_image failed\n");
		exit(EXIT_FAILURE);
	}

	game->img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->img)
	{
		printf("Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}

	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		printf("Error: mlx_image_to_window failed");
		exit(EXIT_FAILURE);
	}
}
