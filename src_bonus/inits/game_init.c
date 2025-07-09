/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:44:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 23:27:18 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	exit_with_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	local_exit_clean_with_msg(char *msg, t_game *game)
{
	free_textures(game);
	mlx_terminate(game->mlx);
	free_map(game->map->map);
	free_trims(game->map);
	free_images(game);
	exit_with_msg(msg);
}

void	load_textures(t_game *game)
{
	game->textures->n_wall_texture = mlx_load_png(game->map->north_path);
	game->textures->e_wall_texture = mlx_load_png(game->map->east_path);
	game->textures->s_wall_texture = mlx_load_png(game->map->south_path);
	game->textures->w_wall_texture = mlx_load_png(game->map->west_path);
	if (!game->textures->n_wall_texture || !game->textures->e_wall_texture
		|| !game->textures->s_wall_texture || !game->textures->w_wall_texture)
		local_exit_clean_with_msg("Error: mlx_load_png failed\n", game);
	game->textures->n_wall_img = mlx_texture_to_image(game->mlx,
			game->textures->n_wall_texture);
	game->textures->e_wall_img = mlx_texture_to_image(game->mlx,
			game->textures->e_wall_texture);
	game->textures->s_wall_img = mlx_texture_to_image(game->mlx,
			game->textures->s_wall_texture);
	game->textures->w_wall_img = mlx_texture_to_image(game->mlx,
			game->textures->w_wall_texture);
	if (!game->textures->n_wall_img || !game->textures->e_wall_img
		|| !game->textures->s_wall_img || !game->textures->w_wall_img)
		local_exit_clean_with_msg("Error: mlx_texture_to_image failed\n", game);
}

void	game_init(t_game *game)
{
	game->mlx = mlx_init(1920, 1080, "cub3D", true);
	if (!game->mlx)
		error_exit("Error: mlx_init failed\n");
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		exit_with_msg("Error: malloc failed for textures");
	load_textures(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	game->img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->img)
		local_exit_clean_with_msg("Error: mlx_new_image failed\n", game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		local_exit_clean_with_msg("Error: mlx_image_to_window failed\n", game);
	game->last_mouse_x = 960;
}
