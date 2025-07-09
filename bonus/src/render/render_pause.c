/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:48:56 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 23:39:55 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	clear_pause_overlay(t_game *game)
{
	if (game->pause_text)
	{
		mlx_delete_image(game->mlx, game->pause_text);
		game->pause_text = NULL;
	}
	if (game->resume_text)
	{
		mlx_delete_image(game->mlx, game->resume_text);
		game->resume_text = NULL;
	}
}

void	render_pause_screen(t_game *game, int show)
{
	if (show)
	{
		if (!game->pause_text)
			game->pause_text = mlx_put_string(game->mlx, "PAUSED", 20, 20);
		if (!game->resume_text)
			game->resume_text = mlx_put_string(game->mlx,
					"Press TAB to resume", 20, 50);
		if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		{
			mlx_close_window(game->mlx);
			return ;
		}
	}
	else
		clear_pause_overlay(game);
}
