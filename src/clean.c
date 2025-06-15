/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:48:27 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/12 17:48:51 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void free_trims(t_map *map)
{
	if (map->north_path)
		free(map->north_path);
	if (map->south_path)
		free(map->south_path);
	if (map->west_path)
		free(map->west_path);
	if (map->east_path)
		free(map->east_path);
}

void free_images(t_game *game)
{
	if (!game || !game->textures)
		return;

	if (game->textures->n_wall_img)
		mlx_delete_image(game->mlx, game->textures->n_wall_img);
	if (game->textures->e_wall_img)
		mlx_delete_image(game->mlx, game->textures->e_wall_img);
	if (game->textures->s_wall_img)
		mlx_delete_image(game->mlx, game->textures->s_wall_img);
	if (game->textures->w_wall_img)
		mlx_delete_image(game->mlx, game->textures->w_wall_img);
}

void free_textures(t_game *game)
{
	if (!game || !game->textures)
		return;

	if (game->textures->n_wall_texture)
		mlx_delete_texture(game->textures->n_wall_texture);
	if (game->textures->e_wall_texture)
		mlx_delete_texture(game->textures->e_wall_texture);
	if (game->textures->s_wall_texture)
		mlx_delete_texture(game->textures->s_wall_texture);
	if (game->textures->w_wall_texture)
		mlx_delete_texture(game->textures->w_wall_texture);

	free(game->textures);
	game->textures = NULL;
}

void    free_both_textures_and_images(t_game *game)
{
    free_images(game);
    free_textures(game);
}

void	clean_exit(t_game *game, t_map *map)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	free_images(game);
	free_textures(game);
	mlx_terminate(game->mlx);
	free_map(map->map);
	free_trims(map);
}
