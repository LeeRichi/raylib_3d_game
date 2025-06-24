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

void exit_with_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void load_textures(t_game *game)
{
	game->textures->n_wall_texture = mlx_load_png(game->map->north_path);
	game->textures->e_wall_texture = mlx_load_png(game->map->east_path);
	game->textures->s_wall_texture = mlx_load_png(game->map->south_path);
	game->textures->w_wall_texture = mlx_load_png(game->map->west_path);
	if (!game->textures->n_wall_texture || !game->textures->e_wall_texture ||
		!game->textures->s_wall_texture || !game->textures->w_wall_texture)
	{
		printf("Error: mlx_load_png failed\n");
		free_textures(game);
		exit(EXIT_FAILURE);
	}

	game->textures->n_wall_img = mlx_texture_to_image(game->mlx, game->textures->n_wall_texture);
	game->textures->e_wall_img = mlx_texture_to_image(game->mlx, game->textures->e_wall_texture);
	game->textures->s_wall_img = mlx_texture_to_image(game->mlx, game->textures->s_wall_texture);
	game->textures->w_wall_img = mlx_texture_to_image(game->mlx, game->textures->w_wall_texture);

	if (!game->textures->n_wall_img || !game->textures->e_wall_img ||
		!game->textures->s_wall_img || !game->textures->w_wall_img)
	{
		printf("Error: mlx_texture_to_image failed\n");
		free_images(game);
		free_textures(game);
		exit(EXIT_FAILURE);
	}
}

void game_init(t_game *game)
{

	game->map->ceiling_color = 0x000000FF;
	game->map->floor_color = 0xD3D3D3D3;

	game->mlx = mlx_init(1920, 1080, "cub3D", true);
	if (!game->mlx)
	{
		printf("Error: mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		exit_with_msg("Error: malloc failed for textures");

	load_textures(game);

	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);

	// game->textures = malloc(sizeof(t_textures));
	// if (!game->textures)
	// {
	// 	printf("Error: malloc failed for textures\n");
	// 	exit(EXIT_FAILURE);
	// }

	// load_textures(game);

	// game->textures->n_wall_texture = mlx_load_png(game->map->north_path);
	// game->textures->e_wall_texture = mlx_load_png(game->map->east_path);
	// game->textures->s_wall_texture = mlx_load_png(game->map->south_path);
	// game->textures->w_wall_texture = mlx_load_png(game->map->west_path);
	// if (!game->textures->n_wall_texture || !game->textures->e_wall_texture ||
	// 	!game->textures->s_wall_texture || !game->textures->w_wall_texture)
	// {
	// 	printf("Error: mlx_load_png failed\n");
	// 	free_textures(game); // only textures exist so far
	// 	exit(EXIT_FAILURE);
	// }

	// game->textures->n_wall_img = mlx_texture_to_image(game->mlx, game->textures->n_wall_texture);
	// game->textures->e_wall_img = mlx_texture_to_image(game->mlx, game->textures->e_wall_texture);
	// game->textures->s_wall_img = mlx_texture_to_image(game->mlx, game->textures->s_wall_texture);
	// game->textures->w_wall_img = mlx_texture_to_image(game->mlx, game->textures->w_wall_texture);

	// if (!game->textures->n_wall_img || !game->textures->e_wall_img ||
	// 	!game->textures->s_wall_img || !game->textures->w_wall_img)
	// {
	// 	printf("Error: mlx_texture_to_image failed\n");
	// 	free_images(game);
	// 	free_textures(game);
	// 	exit(EXIT_FAILURE);
	// }

	game->img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->img)
	{
		printf("Error: mlx_new_image failed\n");
		free_images(game);
		free_textures(game);
		exit(EXIT_FAILURE);
	}

	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		printf("Error: mlx_image_to_window failed\n");
		mlx_delete_image(game->mlx, game->img);
		free_images(game);
		free_textures(game);
		exit(EXIT_FAILURE);
	}


	game->last_mouse_x = 960;
}
